#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

template <typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void insert(const T& data);
    void remove(const T& data);
    bool search(const T& data) const;
    void display() const;

private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
};

// Implementations go here
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    // Free all nodes
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// ... other implementations ...
template <typename T>
void LinkedList<T>::insert(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    Node* current = head;
    if (current == nullptr) {
        head = newNode;
        return;
    }
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

template <typename T>
void LinkedList<T>::remove(const T& data) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }
}

template <typename T>
bool LinkedList<T>::search(const T& data) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
void LinkedList<T>::display() const {
    if (head == nullptr) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << current->data << std::endl;
}

#endif // LINKED_LIST_H