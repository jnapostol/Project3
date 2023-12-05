#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

void swap(tuple<float, string, float, float, float> *x, tuple<float, string, float, float, float> *y); // Swaps two tuples

class MaxHeap { // Heap class
    tuple<float, string, float, float, float> *heapArr; // Tuple heap array to store Agent data:
    // Win-rate, Agent name, Pick-rate, ACS, KDA ratio
    int capacity;
    int heapSize;

public:

    MaxHeap(int cap); // Constructs heap with capacity from main
    int parent(int i) { return (i-1)/2; } // Gets the parent of an index
    int left(int i) { return (2*i + 1); } // Gets the left child of an index
    int right(int i) { return (2*i + 2); } // Gets the right child of an index

    tuple<float, string, float, float, float> extractMax(); // Extracts the max in the heap (sorted by Agent's win-rate)
    void Insert(tuple<float, string, float, float, float> data); // Inserts each agent into the heap with their data
    void HeapifyDown(int parentIndex); // Heapify down after extracting the max, using the parent index
};

MaxHeap::MaxHeap(int cap) { // Construct the heap array with a capacity
    heapSize = 0;
    capacity = cap;
    heapArr = new tuple<float, string, float, float, float>[capacity];
}

void MaxHeap::Insert(tuple<float, string, float, float, float> data) { // Insert agents into the heap (17 total)
    heapSize++; // Increase heap size
    int i = heapSize - 1; // Get the index of the last position in the heap
    heapArr[i] = data; // Insert agent to the end of the heap

    while (i != 0 && get<0>(heapArr[parent(i)]) < get<0>(heapArr[i])) // If the win-rate of the parent data is less
        // than the current win-rate of the data
    {
        swap(&heapArr[i], &heapArr[parent(i)]); // Swap the parent and the current data
        i = parent(i); // Update the last position to be the parent's position
    }
}

tuple<float, string, float, float, float> MaxHeap::extractMax() { // Extracts the max in the heap (sorted by win-rate)
    tuple<float, string, float, float, float> temp = heapArr[0]; // Store the root into a temp variable
    heapArr[0] = heapArr[heapSize-1]; // Set the last element in the heap equal to the root
    heapSize--; // Decrease the heap size

    HeapifyDown(0); // Heapify down

    return temp; // Return the Agent's tuple data
}

void MaxHeap::HeapifyDown(int parentIndex) { // Heapify down after extracting the max
    int leftIndex = (2*parentIndex) + 1; // Get left index
    int rightIndex = (2*parentIndex) +2; // Get right index
    int maxIndex = parentIndex; // Get the current max, which is the passed in parameter

    if (rightIndex < heapSize && heapArr[rightIndex] > heapArr[maxIndex]) { // When the right index is greater
        maxIndex = rightIndex; // Update the max to be the right
    }

    if (leftIndex < heapSize && heapArr[leftIndex] > heapArr[maxIndex]) { // When the left index is greater
        maxIndex = leftIndex; // Update the max to be the left
    }

    if(maxIndex != parentIndex) { // When the max index isn't the parent index
        swap(&heapArr[parentIndex], &heapArr[maxIndex]); // Swap the parent and the max
        HeapifyDown(maxIndex);
    }
}

void swap(tuple<float, string, float, float, float> *x, tuple<float, string, float, float, float> *y) { // Swaps data
    tuple<float, string, float, float, float> temp = *x;
    *x = *y;
    *y = temp;
}