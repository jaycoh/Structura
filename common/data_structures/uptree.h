#ifndef UPTREE_H
#define UPTREE_H

#include <vector>
#include <stdexcept>

// Simple union-find (uptree) implementation with path compression and union by rank.
class Uptree {
public:
    explicit Uptree(int n) {
        if (n <= 0) throw std::invalid_argument("size must be positive");
        parent_.resize(n);
        rank_.assign(n, 0);
        for (int i = 0; i < n; ++i) parent_[i] = i;
    }

    int find(int x) {
        checkIndex(x);
        if (parent_[x] == x) return x;
        parent_[x] = find(parent_[x]);
        return parent_[x];
    }

    void unite(int a, int b) {
        checkIndex(a);
        checkIndex(b);
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return;
        if (rank_[ra] < rank_[rb]) {
            parent_[ra] = rb;
        } else if (rank_[rb] < rank_[ra]) {
            parent_[rb] = ra;
        } else {
            parent_[rb] = ra;
            ++rank_[ra];
        }
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }

    int size() const { return static_cast<int>(parent_.size()); }

private:
    std::vector<int> parent_;
    std::vector<int> rank_;

    void checkIndex(int x) const {
        if (x < 0 || x >= static_cast<int>(parent_.size())) {
            throw std::out_of_range("index out of range");
        }
    }
};

#endif // UPTREE_H
