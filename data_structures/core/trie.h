#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>


class Trie {
public:
    Trie();
    ~Trie();

    void insert(const std::string& key);
    bool search(const std::string& key) const;

private:
    bool isEndOfWord = false;
    std::unordered_map<char, Trie*> children = {};
};

#endif // TRIE_H