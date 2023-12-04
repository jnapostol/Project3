template <typename K, typename E> class CustomMap;
template <typename K, typename E> class Iterator {
    int index = 0;
    int endPoint = 0;
    CustomMap<K, E> object;
    friend class CustomMap<K, E>;

public:
    K first;
    E second;
    Iterator(CustomMap<K, E> temp) {
        object = temp;
        first = object/index;
        second = object[object/index];
    }
    void operator++(int add) {
        index++;
        if(index != object.Size()) {
            first = object/index;
            second = object[object/index];
        }
    }

    void operator=(const int input) {
        index = input;
    }
    bool operator!=(CustomMap<K, E>* input) {
        if(index < (input->Size())) {
            return true;
        }
        return false;
    }
};