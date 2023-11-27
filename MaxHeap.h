#include <iostream>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// using a priority queue (max heap) with tuple

priority_queue<tuple<int, float, string>> name; // syntax for pq
tuple<int, float, string> Tuple = name.top(); // getting the max elements in the heap
cout << get<0>(Tuple) << endl;













/*
void heapifyUp(int arr[], int size, int parentIndex){

    // loop through the array
    //


 assert (0 <= pos && pos < n) : "Invalid heap position";
    while (pos > 0) {
      int parent = parent(pos);
      if (isGreaterThan(parent, pos)) {
        return; // stop early
      }
      swap(pos, parent);
      pos = parent; // keep sifting up
    }

}

void insert(int arr[], int size, int n){
    size = size + 1; // increase heap size
    arr[size-1] = n; // insert element at the end of heap
    heapifyUp(arr, size, size-1); // heapify up
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

int* extractMax(int arr[], int size) // return the data we want (most wins/most kills associated with an agent) might use with a priority queue?
{
    // set the last element equal to the first
    arr[0] = arr[size-1];

    //heapify down function w/ updated size
    heapifyDown(arr, size - 1, 0);

    return arr;
}

*/