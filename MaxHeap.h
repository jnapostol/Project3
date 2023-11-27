#include <iostream>
#include <algorithm>
#include <string>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

// using a priority queue (max heap) with tuple

priority_queue<tuple<float, float, float, float, string>> pq; // winrate, pickrate, acs, kda, agent
tuple<float, float, float, float, string> Tuple = pq.top(); // getting the max elements in the heap
tuple<float, float, float, float, string> _data = make_tuple(10.0,50.0, 555.1, 66.2, "friend"); // initializing the tuple with values

void function() {
    Tuple = _data; // assigning tuple to values

    int ex = get<0>(Tuple); // is how to get the first tuple element aka the winrate
    int ex2 = get<1>(Tuple); // is how to get the first tuple element aka the winrate
    int ex3 = get<2>(Tuple); // is how to get the first tuple element aka the winrate
    int ex4 = get<3>(Tuple); // is how to get the first tuple element aka the winrate
    string ex5 = get<4>(Tuple); // is how to get the first tuple element aka the winrate

    pq.pop(); // gets rid of the root (max in heap);
};












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