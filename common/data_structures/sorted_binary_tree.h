#ifndef SORTED_BINARY_TREE_H
#define SORTED_BINARY_TREE_H

#include <iostream>
#include <stdexcept>
#include "binary_tree.h"

template <typename T>
class SortedBinaryTree : public BinaryTree<T> {
public:
    SortedBinaryTree(const T& data) : BinaryTree<T>(data) {}

    bool search(const T& data) const;
    void insert(const T& data);
    void setLeft(std::unique_ptr<BinaryTree<T>> left) override;
    void setRight(std::unique_ptr<BinaryTree<T>> right) override;
    void setData(const T& data) override {
        throw std::logic_error("setData is not supported in SortedBinaryTree");
    }

};

template <typename T>
bool SortedBinaryTree<T>::search(const T& data) const {
    const BinaryTree<T>* current = this;
    while (current != nullptr) {
        if (data == current->getData()) {
            return true;
        } else if (data < current->getData()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    return false;
}

template <typename T>
void SortedBinaryTree<T>::insert(const T& data) {
    // Binary Tree is instantiated with data, so we don't need to check for nullptr.
    BinaryTree<T>* current = this;
    while (current != nullptr) {
        if (data < current->getData()) {
            if (current->getLeft() == nullptr) {
                current->setLeft(std::make_unique<SortedBinaryTree<T>>(data));
                return;
            }
            current = current->getLeft();
        } else {
            if (current->getRight() == nullptr) {
                current->setRight(std::make_unique<SortedBinaryTree<T>>(data));
                return;
            }
            current = current->getRight();
            
        }
    }
}

template <typename T>
void SortedBinaryTree<T>::setLeft(std::unique_ptr<BinaryTree<T>> left) {
    SortedBinaryTree<T>* sortedLeft = left ? dynamic_cast<SortedBinaryTree<T>*>(left.get()) : nullptr;
    if (left && (!sortedLeft || !sortedLeft->isSorted())) {
        throw std::invalid_argument("Left subtree is not sorted");
    }
    if (left && this->getData() < left->getData()) {
        throw std::invalid_argument("Left subtree must be less than parent");
    }
    BinaryTree<T>::setLeft(std::move(left));
}

template <typename T>
void SortedBinaryTree<T>::setRight(std::unique_ptr<BinaryTree<T>> right) {
    SortedBinaryTree<T>* sortedRight = right ? dynamic_cast<SortedBinaryTree<T>*>(right.get()) : nullptr;
    if (right && (!sortedRight || !sortedRight->isSorted())) {
        throw std::invalid_argument("Right subtree is not sorted");
    }
    if (right && this->getData() > right->getData()) {
        throw std::invalid_argument("Right subtree must be greater than parent");
    }
    BinaryTree<T>::setRight(std::move(right));
}

#endif // SORTED_BINARY_TREE_H




