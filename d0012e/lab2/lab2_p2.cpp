#include<iostream>

using namespace std;

void RandomArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 201 + (-100);
    }
}

void PrintArr(int* arr, int size, string Header) {
    cout << Header << ": \n [";
    for (int i = 0; i < size; i++) {
        cout << arr[i];

        if (i + 1 != size) {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

int max(int a, int b, int c) {
    return max(max(a, b), c);
}

struct Node {
    int max;

    int left_max;

    int right_max;

    int sum;
};

Node MaxSubArraySum(int* arr, int l, int r){
    if(l == r){
        Node leaf;
        /* Since this is the last node all of the
        *  values are the same
        */
        leaf.max = arr[l];
        leaf.left_max = arr[l];
        leaf.right_max = arr[l];
        leaf.sum = arr[l];
        return leaf;
    }
    int mid = (r + l) >> 1;
    Node left = MaxSubArraySum(arr, l, mid);
    Node right = MaxSubArraySum(arr, mid+1, r);

    Node merged;

    merged.max = merged.left_max = merged.right_max = merged.sum = 0;

    merged.left_max = max(left.left_max, left.sum + right.left_max, left.sum + right.sum);

    merged.right_max = max(right.right_max, right.sum + left.right_max, left.sum + right.sum);

    merged.sum = left.sum + right.sum;

    int maxL = max(merged.left_max, merged.right_max, merged.sum);
    int maxR = max(left.max, right.max, left.right_max + right.left_max);

    merged.max = max(maxL, maxR);

    return merged;

}

int main() {
    const int size = 10;
    int lst_of_numbers[size];
    //int test[10] = {-1, -30, -45, -2, -3, -10, -11, -9, 1, -2};
    RandomArr(lst_of_numbers, size);
    PrintArr(lst_of_numbers, size, "Intial array: ");
    Node max_sum_node = MaxSubArraySum(lst_of_numbers, 0, size - 1);
    cout << "Max SubArray Sum: " << max_sum_node.max << endl;
    return 0;
}