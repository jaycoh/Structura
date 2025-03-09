#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

template <typename T>
class BinaryTree {
public:
    // If we don't provide data in the constructor, we would have to use default member initialization for data or turn data into a pointer.
    BinaryTree(const T& data) : data(data), left(nullptr), right(nullptr) {}
    ~BinaryTree();

    void setLeft(BinaryTree* left);
    void setRight(BinaryTree* right);
    void setData(const T& data);
    BinaryTree* getLeft() const;
    BinaryTree* getRight() const;
    T getData() const;

private:
    T data;
    BinaryTree* left = nullptr;
    BinaryTree* right = nullptr;
};

template <typename T>
BinaryTree<T>::~BinaryTree() {
    delete left;
    delete right;
}

template <typename T>
void BinaryTree<T>::setLeft(BinaryTree* left) {
    delete this->left;
    this->left = left;
}

template <typename T>
void BinaryTree<T>::setRight(BinaryTree* right) {
    delete this->right;
    this->right = right;
}

template <typename T>
void BinaryTree<T>::setData(const T& data) {
    this->data = data;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::getLeft() const {
    return left;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::getRight() const {
    return right;
}

template <typename T>
T BinaryTree<T>::getData() const {
    return data;
}

#endif // BINARY_TREE_H