#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <memory>

template <typename T>
class BinaryTree {
public:
    // If we don't provide data in the constructor, we would have to use default member initialization for data or turn data into a pointer.
    BinaryTree(const T& data) : data(data), left(nullptr), right(nullptr) {}
    // It is good practice to make the destructor virtual if the class is intended to be derived from.
    virtual ~BinaryTree() = default;

    virtual void setLeft(std::unique_ptr<BinaryTree<T>> left);
    virtual void setRight(std::unique_ptr<BinaryTree<T>> right);
    virtual void setData(const T& data);
    BinaryTree* getLeft() const;
    BinaryTree* getRight() const;
    T getData() const;

protected:
    bool isSorted() const;

private:
    T data;
    std::unique_ptr<BinaryTree<T>> left = nullptr;
    std::unique_ptr<BinaryTree<T>> right = nullptr;
};



template <typename T>
void BinaryTree<T>::setLeft(std::unique_ptr<BinaryTree<T>> left) {
    this->left = std::move(left);
}

template <typename T>
void BinaryTree<T>::setRight(std::unique_ptr<BinaryTree<T>> right) {
    this->right = std::move(right);
}

template <typename T>
void BinaryTree<T>::setData(const T& data) {
    this->data = data;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::getLeft() const {
    return left.get();
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::getRight() const {
    return right.get();
}

template <typename T>
T BinaryTree<T>::getData() const {
    return data;
}

template <typename T>
bool BinaryTree<T>::isSorted() const {
    // 'this' cannot be null for a well-formed member function call; remove that check.
    if (left != nullptr && left->getData() > data) {
        return false;
    }
    if (right != nullptr && right->getData() < data) {
        return false;
    }
    // Only recurse when children are non-null to avoid dereferencing null pointers.
    return (left == nullptr || left->isSorted()) && (right == nullptr || right->isSorted());
}

#endif // BINARY_TREE_H