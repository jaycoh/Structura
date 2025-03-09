#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

template <typename T>
class BinaryTree {
public:
    // If we don't provide data in the constructor, we would have to use default member initialization for data or turn data into a pointer.
    BinaryTree(const T& data) : data(data), left(nullptr), right(nullptr) {}
    // It is good practice to make the destructor virtual if the class is intended to be derived from.
    virtual ~BinaryTree();

    virtual void setLeft(BinaryTree* left);
    virtual void setRight(BinaryTree* right);
    virtual void setData(const T& data);
    BinaryTree* getLeft() const;
    BinaryTree* getRight() const;
    T getData() const;

protected:
    bool isSorted() const;

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

template <typename T>
bool BinaryTree<T>::isSorted() const {
    if (this == nullptr) {
        return true;
    }
    if (left != nullptr && left->getData() > data) {
        return false;
    }
    if (right != nullptr && right->getData() < data) {
        return false;
    }
    return left->isSorted() && right->isSorted();
}

#endif // BINARY_TREE_H