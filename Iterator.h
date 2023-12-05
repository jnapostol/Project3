template <typename K, typename E> class CustomMap;
template <typename K, typename E> class Iterator {
    int index = 0;
    int endPoint = 0;
    CustomMap<K, E> object;
    friend class CustomMap<K, E>; // Allows us to access private aspects of CustomMap without #include

public:
    K first; // A reference to the key
    E second; // Reference to the appropriate element
    Iterator(CustomMap<K, E> temp) {
        object = temp;
        first = object/index; // Uses / operator in CustomMap that returns the sortedKey at index
        second = object[object/index];
    }
    void operator++(int add) {
        index++;
        if(index != object.Size()) { // Avoid out of range exception
            first = object/index; // Update values
            second = object[object/index];
        }
    }

    void operator=(const int input) { // Assignment operator for it = mapObject.Begin()
        index = input;
    }
    bool operator!=(CustomMap<K, E>* input) {
        if(index < (input->Size())) {
            return true;
        }
        return false; // Return false when index is greater than the size of the object we are iterating through
    }
};