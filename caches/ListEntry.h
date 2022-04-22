#ifndef LIST_ENTRY_H
#define LIST_ENTRY_H

#include <iostream>

template<typename K, typename V>
struct ListEntry {

public:
    ListEntry(K key, V value) {
        this->key = key;
        this->value = value;
    }

    K key;
    V value;
    int fr_key = 1;
};

#endif
