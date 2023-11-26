#include <iostream>
#include <algorithm>
using namespace std;

void heapifyDown(int arr[], int size, int parentIndex);

int* extractMax(int arr[], int size)
{
    // set the last element equal to the first
    arr[0] = arr[size-1];

    //heapify down function w/ updated size
    heapifyDown(arr, size - 1, 0);

    return arr;
}

void heapifyDown(int arr[], int size, int parentIndex) {
    int leftIndex = (2*parentIndex) + 1;
    int rightIndex = (2*parentIndex) +2;
    int maxIndex = parentIndex;

    if (rightIndex < size && arr[rightIndex] > arr[maxIndex]) {
        maxIndex = rightIndex;
    }

    if (leftIndex < size && arr[leftIndex] > arr[maxIndex]) {
        maxIndex = leftIndex;
    }

    if(maxIndex != parentIndex) {
        swap(arr[parentIndex], arr[maxIndex]);
        heapifyDown(arr, size, maxIndex);
    }
}