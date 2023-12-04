#include <tuple>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

template <typename K, typename E> class CustomMap {
    int size = 0;
    vector<K> sortedKeys; //keys sorted in descending order
    vector<K> keyContainer; //keys sorted in insertion order
    vector<E> elementContainer; //elements sorted in insertion order

    int GetElementIndexOfKey(K key) {
        for (int i = 0; i < size; i++) {
            if(keyContainer[i] == key) {
                return i;
            }
        }
        cout<<"key not found" <<endl;
        return 0;
    }
public:
    int Begin() {
        return 0;
    }
    CustomMap<K, E>* End() {
        return this;
    }
    E operator[](K key) {
        return elementContainer.at(GetElementIndexOfKey(key));
    }
    K operator/(int index) {
        return sortedKeys.at(index);
    }
    void Insert(K key, E element) {//does not prevent duplicates
        sortedKeys.push_back(key);
        sort(sortedKeys.begin(), sortedKeys.end(), greater<K>());
        keyContainer.push_back(key);
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