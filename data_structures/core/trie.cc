#include "trie.h"

Trie::Trie() = default;

Trie::~Trie() {
    for (auto& [key, value] : children) {
        delete value;
    }
}

void Trie::insert(const std::string& key) {
    Trie* current = this;
    for (const char& c : key) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new Trie();
        }
        current = current->children[c];
    }
    current->isEndOfWord = true;
}

bool Trie::search(const std::string& key) const {
    const Trie* current = this;
    for (const char& c : key) {
        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children.at(c);
    }
    return current->isEndOfWord;
}