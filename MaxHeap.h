#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

void swap(tuple<float, string, float, float, float> *x, tuple<float, string, float, float, float> *y);

class MaxHeap {
    tuple<float, string, float, float, float> *heapArr;
    int capacity;
    int heapSize;

public:

    MaxHeap(int cap);
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }

    tuple<float, string, float, float, float> extractMax();
    void Insert(tuple<float, string, float, float, float> data);
    void heapifyDown(int parentIndex);
};

MaxHeap::MaxHeap(int cap) {
    heapSize = 0;
    capacity = cap;
    heapArr = new tuple<float, string, float, float, float>[capacity];

}

void MaxHeap::Insert(tuple<float, string, float, float, float> data) { // insert 17 agents into the heap
    //cout << "INSERTED" << endl;
    heapSize++;

    int i = heapSize - 1;

    heapArr[i] = data;

    while (i != 0 && get<0>(heapArr[parent(i)]) < get<0>(heapArr[i]))
    {
        swap(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }


}

tuple<float, string, float, float, float> MaxHeap::extractMax()
{
    // set the last element equal to the first
    tuple<float, string, float, float, float> temp = heapArr[0];
    heapArr[0] = heapArr[heapSize-1];
    heapSize--;
    //heapify down function w/ updated size
    heapifyDown(0);

    return temp;
}

void MaxHeap::heapifyDown(int parentIndex) {
    int leftIndex = (2*parentIndex) + 1;
    int rightIndex = (2*parentIndex) +2;
    int maxIndex = parentIndex;

    if (rightIndex < heapSize && heapArr[rightIndex] > heapArr[maxIndex]) {
        maxIndex = rightIndex;
    }

    if (leftIndex < heapSize && heapArr[leftIndex] > heapArr[maxIndex]) {
        maxIndex = leftIndex;
    }

    if(maxIndex != parentIndex) {
        swap(&heapArr[parentIndex], &heapArr[maxIndex]);
        heapifyDown(maxIndex);
    }
}

void swap(tuple<float, string, float, float, float> *x, tuple<float, string, float, float, float> *y)
{
    tuple<float, string, float, float, float> temp = *x;
    *x = *y;
    *y = temp;
}
