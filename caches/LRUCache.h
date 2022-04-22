#ifndef LRUCACHE_H
#define LURCACHE_H

#include <list>
#include <unordered_map>
#include <assert.h>
#include <iostream>

template<typename KeyT, typename T>
class LRUCache
{

using ListItr = typename std::list<KeyT>::iterator;

public:
    LRUCache(int size) : m_size(size)
    {

    }

    int size() const
    {
        return m_size;
    }

    int capacity() const
    {
        return m_capacity;
    }

    bool isFull() const
    {
        return m_size == m_cache.size();
    }

    bool contains(const KeyT& key)
    {
        m_lookup_table.find(key) != m_lookup_table.end();
    }

    void display() const
    {
        for (const auto& e : m_cache) {
            std::cout << m_lookup_table.at(e).first << " ";
        }
        std::cout << std::endl;
    }

    T get(const KeyT& key)
    {
        auto hit = m_lookup_table.find(key);
        assert("No such element present" && hit != m_lookup_table.end());
        if (hit->second.second != m_cache.begin()) {
            m_cache.splice(m_cache.begin(), m_cache, hit->second.second);
        }
        return hit->second.first;
    }

    void set(const KeyT& key, const T& value)
    {
        if (isFull()) {
            erase();
        }
        m_cache.push_front(key);
        m_lookup_table.emplace(key, std::pair<T, ListItr>(value, m_cache.begin()));
        ++m_capacity;
    }


private:
    void erase()
    {
        assert("Erasing cannot be performed, cache is not full." && isFull());
        auto toDelete = m_lookup_table.find(m_cache.back());
        assert("Erasing cannot be performed. LRU element is not present in the lookup table" && toDelete != m_lookup_table.end());

        m_cache.pop_back();
        m_lookup_table.erase(toDelete);
        --m_capacity;
    }

    int m_size;
    int m_capacity = 0;
    std::list<KeyT> m_cache;
    std::unordered_map<KeyT, std::pair<T, ListItr>> m_lookup_table;
};

#endif
