#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "linked_list.h"
static_assert(sizeof(LinkedList<int>) > 0, "LinkedList must be defined");
#include <unordered_map>
#include <utility>  // For std::pair

template <typename K, typename V>
class LRUCache {
public:
    LRUCache(int capacity);
    ~LRUCache();

    // Returns a nullptr on miss. This is more common than throwing an exception.
    V* get(const K& key);
    void put(const K& key, const V& value);

private:
    int capacity_;
    LinkedList<K> order_;
    std::unordered_map<K, std::pair<V, typename LinkedList<K>::Node*>> cache_;
};

template <typename K, typename V>
LRUCache<K, V>::LRUCache(int capacity) : capacity_(capacity) {}

template <typename K, typename V>
LRUCache<K, V>::~LRUCache() {}

template <typename K, typename V>
V* LRUCache<K, V>::get(const K& key) {
    auto it = cache_.find(key);
    if (it == cache_.end()) {
        return nullptr;
    }

    LinkedList<K>::removeNode(it->second.second, &order_);
    order_.insert(key);
    it->second.second = order_.getHead();
    return &it->second.first;
}

template <typename K, typename V>
void LRUCache<K, V>::put(const K& key, const V& value) {
    if (capacity_ <= 0) return;
    auto it = cache_.find(key);
    if (it != cache_.end()) {
        LinkedList<K>::removeNode(it->second.second, &order_);
        cache_.erase(it);
    } else if (cache_.size() >= capacity_) {
        K keyToRemove = order_.getTail()->data;
        typename LinkedList<K>::Node* nodeToRemove = order_.getTail();
        cache_.erase(keyToRemove);
        LinkedList<K>::removeNode(nodeToRemove, &order_);
    }

    order_.insert(key);
    cache_[key] = {value, order_.getHead()};
}

#endif // LRU_CACHE_H