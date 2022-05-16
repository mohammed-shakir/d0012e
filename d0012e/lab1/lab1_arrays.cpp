#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <chrono>
#include <math.h>

using namespace std;


int binarySearch(int* a, int item, int low, int high) {
    if (high <= low) {
        return (item > a[low]) ? (low + 1) : low;
    }

    int mid = (low + high) / 2;
 
    if (item == a[mid]) {
        return mid + 1;
    } 

    if (item > a[mid]) {
        return binarySearch(a, item, mid + 1, high);
    }

    return binarySearch(a, item, low, mid - 1);
}

void bSort(int* a, int n) {
    int i, loc, j, k, selected;
 
    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = a[i];
 
        loc = binarySearch(a, selected, 0, j);
 
        while (j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
}

void PrintArr(int* arr, int size, string Header){
    cout << Header << ": \n [";
    for(int i = 0; i < size; i++){
        cout << arr[i];
        if(i + 1 != size){
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void insertion_sort(int* array, int l, int r)
{
    int tmp, j;
    for (int i = l; i <= r; i++)
    {
        tmp = array[i];
        j = i - 1;
        while ((j >= l) && (array[j] > tmp))
        {
             array[j + 1] = array[j];
             j--;
        }
        array[j + 1] = tmp;
    }
}

void merge(int* arr, int* temp, int l, int m, int r)
{
    int i = l;
    int j = m + 1;
    int k = l;
    while ((i <= m) && (j <= r))
    {
        if (arr[i] < arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

        for (; j <= r; j++, k++)
            temp[k] = arr[j];

        for (; i <= m; i++, k++)
            temp[k] = arr[i];

        for (i = l; i <= r; i++)
            arr[i] = temp[i];
}

void insertion_mergesort(int* arr, int* temp, int l, int r, int k, int size)
{
    if (l < r)
    {
        if (size <= k){
            insertion_sort(arr, l, r);
        }
        else
        {
            int m = size / k;
            int right_size = size - m;
            int middle = l + (r - l)/2;
            insertion_mergesort(arr, temp, l, middle, k, m);
            insertion_mergesort(arr, temp, middle+1, r, k, right_size);
            merge(arr, temp, l, middle, r);
        }
    }
}

void bsort_mergesort(int* arr, int* temp, int l, int r, int k, int size)
{
    if (l < r)
    {
        if (size <= k)
            bSort(arr, size);
        else
        {
            int m = size / k;
            int right_size = size - m;
            int middle = l + (r - l)/2;
            bsort_mergesort(arr, temp, l, middle, k, m);
            bsort_mergesort(arr, temp, middle + 1, r, k, right_size);
            merge(arr, temp, l, middle, r);
        }
    }
}

void RandomArr(int* insertion_arr, int* bsort_arr, int size){
    for(int i = 0; i < size; i++){
        int random = rand() % 100 +1;
        insertion_arr[i] = random;
        bsort_arr[i] = random;
    }
}

void AlmostSortedArr(int* insertion_arr, int* bsort_arr, int size){
    for(int i = 0; i < size; i++){
        int b = i / 100;
        if(b*100 == i ){
            int random = rand() % 100 +1;
            insertion_arr[i] = random;
            bsort_arr[i] = random;
        }
        else{
            insertion_arr[i] = i;
            bsort_arr[i] = i;
        }
        
    }
}

void SortedArr(int* insertion_arr, int* bsort_arr, int size){
    for(int i = 0; i < size; i++){
        insertion_arr[i] = i;
        bsort_arr[i] = i;    
    }
}

void TestTime(int tries, int bsort_k, int insert_k, int size){
    int insertion_array[size];
    int bsort_array[size];
    //RandomArr(insertion_array, bsort_array, size);
    //AlmostSortedArr(insertion_array, bsort_array, size);
    SortedArr(insertion_array, bsort_array, size);
    int * insertion_temp = new int[size];
    int * bsort_temp = new int[size];
    double insertion_time_sum = 0.f;
    double bSort_time_sum = 0.f;
    double merge_time_sum = 0.f;
    for(int i = 0; i < tries; i++){
        //insertion
        auto start_insertion_time = chrono::high_resolution_clock::now();
        insertion_mergesort(insertion_array, insertion_temp, 0, size -1, insert_k, size);
        auto end_insertion_time = chrono::high_resolution_clock::now();
        //bsort
        auto start_bsort_time = chrono::high_resolution_clock::now();
        bsort_mergesort(bsort_array, bsort_temp, 0, size -1, bsort_k, size);
        auto end_bsort_time = chrono::high_resolution_clock::now();
        // PrintArr(insertion_array, size, "Insertion Sort array");
        // PrintArr(bsort_array, size, "b Sort array");
        auto insertion_duration = chrono::duration_cast<chrono::microseconds>(end_insertion_time - start_insertion_time);
        auto bsort_duration = chrono::duration_cast<chrono::microseconds>(end_bsort_time - start_bsort_time); 
        insertion_time_sum += insertion_duration.count();
        bSort_time_sum += bsort_duration.count();
    }
    cout << "Insertion total time taken with " << insert_k << " as k value: " << insertion_time_sum/tries << " microseconds \n"<< endl;
    cout << "bSort total time taken " << bsort_k << " as k value: " << bSort_time_sum/tries << " microseconds \n" << endl;
    delete[] insertion_temp;
    delete[] bsort_temp;
}

int main()
{
    string ManualInput;
    int size;
    int insert_k;
    int bsort_k;
    int tries;
    cout << "Array size: " << endl;
    cin >> size;
    cout << "Time average (Will run the sort multiple times and get the average time): " << endl;
    cin >> tries;
    cout << "Manual input?: " << endl;
    cin >> ManualInput;
    if(ManualInput == "yes"){
        cout << "Insertion K value: " << endl;
        cin >> insert_k;
        cout << "bSort K value: " << endl;
        cin >> bsort_k;
        TestTime(tries, bsort_k, insert_k, size);
    }
    else{
        int sizeOfK;
        cout << "How many elements would you like to try: " << endl;
        cin >> sizeOfK;
        int AllK[sizeOfK];
        for(int i = 0; i < sizeOfK; i++){
            cout<<"Insert element "<<i<<": ";
            cin>>AllK[i];
        }
        for(int i = 0; i < sizeOfK; i++){
            TestTime(tries, AllK[i], AllK[i], size);
        }
    }
    return 0;
}