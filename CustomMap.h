#include <tuple>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename K, typename E> class CustomMap {
    int size = 0;
    vector<K> sortedKeys; // Keys sorted in descending order
    vector<K> keyContainer; // Keys sorted in insertion order
    vector<E> elementContainer; // Elements sorted in insertion order

    int GetElementIndexOfKey(K key) { // Key is inputted from sortedKeys
        for (int i = 0; i < size; i++) {
            if(keyContainer[i] == key) { // We find what index it has in the keyContainer (insertion order)
                return i; // We return that index as it corresponds to the appropriate element in element container
            }
        }
        cout<<"key not found" <<endl;
        return 0;
    }
public:
    int Begin() { // it = mapObject.Begin(); returns 0 as a starting index to our iterator
        return 0;
    }
    CustomMap<K, E>* End() { // returns the object itself to allow iterator to check its size
        return this;
    }
    E operator[](K key) {
        return elementContainer.at(GetElementIndexOfKey(key)); //returns element at sortedKey
    }
    K operator/(int index) {
        return sortedKeys.at(index); // Used in Iterator.h to allow it acess to the index
    }
    void Insert(K key, E element) { // Does not prevent duplicates
        sortedKeys.push_back(key);
        sort(sortedKeys.begin(), sortedKeys.end(), greater<K>()); //sorts in descending order
        keyContainer.push_back(key); // If you insert ("games", 56) games in this index has the same index as 56 in element container
        elementContainer.push_back(element);
        size++;
    }
    void Clear() {
        size = 0;
        sortedKeys.clear();
        keyContainer.clear();
        elementContainer.clear();
    }
    int Size() {
        return size;
    }
};