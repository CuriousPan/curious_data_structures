#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include <map>
#include <list>
#include "ListEntry.h"
#include "assert.h"
#include <iostream>

template<typename K, typename V>
class LFUCache
{
    using ListItr = typename std::list<ListEntry<K, V>>::iterator;

public:
    LFUCache(int size) : m_size(size)
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
        return m_cache.size() == m_size;
    }

    bool contains(const K& key) const
    {
        return m_cache.find(key) != m_cache.end();
    }

    void set(const K& key, const V& value)
    {
        if (isFull()) {
            erase();
        }

        auto fr_1 = m_frequency_map.find(1);
        if (fr_1 == m_frequency_map.end()) { //No frequency number 1
            m_frequency_map.emplace(1, std::list<ListEntry<K, V>>());
        }
        m_frequency_map.at(1).push_front(ListEntry<K, V>(key, value));
        m_cache.emplace(key, m_frequency_map.at(1).begin());
        ++m_capacity;
    }

    V get(const K& key)
    {
        auto hit = m_cache.find(key);
        assert("No such element present" && hit != m_cache.end());
        auto higher_fr_list = m_frequency_map.find(hit->second->fr_key + 1);
        if (higher_fr_list == m_frequency_map.end()) { // Higher frequency doesn't exist
            m_frequency_map.emplace(hit->second->fr_key + 1, std::list<ListEntry<K, V>>());
        }
        m_frequency_map.at(hit->second->fr_key + 1).splice(m_frequency_map.at(hit->second->fr_key + 1).begin(),
                                                           m_frequency_map.at(hit->second->fr_key),
                                                           hit->second);
        if (m_frequency_map.at(hit->second->fr_key).size() == 0) {
            m_frequency_map.erase(hit->second->fr_key);
        }
        ++hit->second->fr_key;
        return hit->second->value;
    }

    void display() const
    {
        for (const auto& e : m_cache) {
            std::cout << e.second->value << " ";
        }
        std::cout << std::endl;
    }

private:
    void erase()
    {
        assert("Erasing cannot be performed, cache is not full." && isFull());
        auto toDelete = m_frequency_map.begin()->second.back();

        m_cache.erase(toDelete.key);
        m_frequency_map.begin()->second.pop_back();
        if (m_frequency_map.begin()->second.size() == 0) {
            m_frequency_map.erase(m_frequency_map.begin());
        }
        --m_capacity;
    }

private:
    int m_size;
    int m_capacity = 0;
    std::unordered_map<K, ListItr> m_cache;
    std::map<int, std::list<ListEntry<K, V>>> m_frequency_map;
};

#endif
