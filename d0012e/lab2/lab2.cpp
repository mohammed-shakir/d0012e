#include <iostream>

using namespace std;

void RandomArr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
}

void PrintArr(int *arr, int size, string Header)
{
    cout << Header << ": \n [";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i + 1 != size)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void DVD(int *arr, int *answer, int l, int r)
{
    if (r - l + 1 == 3)
    {
            for (int i = 0; i <= 2; i++)
            {
                if (arr[l + i] < answer[0])
                {
                    answer[2] = answer[1];
                    answer[1] = answer[0];
                    answer[0] = arr[l + i];
                }
                else if (arr[l + i] < answer[1] && arr[l + i] != answer[0])
                {
                    answer[2] = answer[1];
                    answer[1] = arr[l + i];
                }
                else if (arr[l + i] < answer[2] && arr[l + i] != answer[1] && arr[l + i] != answer[0])
                {
                    answer[2] = arr[l + i];
                }
            }
    }
    else{
        int mid = (r + l) / 2;
        DVD(arr, answer, l, l + mid);
        DVD(arr, answer, l + mid + 1, r);
    }
}

void Inc(int *arr, int *answer, int l, int r)
{
    if ((r - l) < 0)
    {
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        if (arr[l + i] < answer[0])
        {
            answer[2] = answer[1];
            answer[1] = answer[0];
            answer[0] = arr[l + i];
        }
        else if (arr[l + i] < answer[1] && arr[l + i] != answer[0])
        {
            answer[2] = answer[1];
            answer[1] = arr[l + i];
        }
        else if (arr[l + i] < answer[2] && arr[l + i] != answer[1] && arr[l + i] != answer[0])
        {
            answer[2] = arr[l + i];
        }
    }
    Inc(arr, answer, l + 3, r);
}

int main()
{
    const int size = 6;
    int *lst_of_numbers = new int[size];
    RandomArr(lst_of_numbers, size);
    int inc_answer[3]={INT_MAX,INT_MAX,INT_MAX};
    int divide_answer[3]={INT_MAX,INT_MAX,INT_MAX};
    PrintArr(lst_of_numbers, size, "Intial array: ");
    Inc(lst_of_numbers, inc_answer, 0, size - 1);
    //DVD(lst_of_numbers,0, size-1);
    DVD(lst_of_numbers, divide_answer, 0, size - 1);
    delete[] lst_of_numbers;
    PrintArr(inc_answer, 3, "Lower values using incremental: ");
    PrintArr(divide_answer, 3, "Lower values using divide and conquer: ");

    return 0;
}