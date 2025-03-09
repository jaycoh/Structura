// data_structures/core/linked_list.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>
#include <iostream>

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* previous;
        Node(const T& value) : data(value), next(nullptr), previous(nullptr) {}
    };

    LinkedList() : head(nullptr), tail(nullptr) {}
\
    void insert(const T& data);  // push_front
    void remove(const T& data);
    bool search(const T& data) const;
    void display() const;

    Node* getHead() const { return head.get(); }
    Node* getTail() const { return tail; }

    void removeNode(Node* nodeToRemove);

private:
    std::unique_ptr<Node> head;
    Node* tail;  // Non-owning pointer to last node

};

template <typename T>
void LinkedList<T>::insert(const T& data) {
    auto newNode = std::make_unique<Node>(data);
    newNode->next = std::move(head);
    if (newNode->next) {
        newNode->next->previous = newNode.get();
    }
    head = std::move(newNode);
    if (!tail) {
        tail = head.get();  // Point to first node
    }
}

template <typename T>
void LinkedList<T>::removeNode(Node* nodeToRemove) {
    if (!nodeToRemove) return;

    if (nodeToRemove == head.get()) {
        head = std::move(nodeToRemove->next);
        if (head) {
            head->previous = nullptr;
        } else {
            tail = nullptr;  // List empty
        }
    } else if (nodeToRemove == tail) {
        tail = nodeToRemove->previous;
        tail->next.reset();
    } else {
        // Temp node takes ownership to ensure deletion when out of scope.
        std::unique_ptr<Node> temp = std::move(nodeToRemove->previous->next);
        if (nodeToRemove->next) {
            nodeToRemove->next->previous = nodeToRemove->previous;
        }
        nodeToRemove->previous->next = std::move(nodeToRemove->next);
    }
}

template <typename T>
void LinkedList<T>::remove(const T& data) {
    Node* current = head.get();
    while (current && current->data != data) {
        current = current->next.get();
    }
    if (current) {
        removeNode(current);
    }
}

template <typename T>
bool LinkedList<T>::search(const T& data) const {
    Node* current = head.get();
    while (current) {
        if (current->data == data) return true;
        current = current->next.get();
    }
    return false;
}

template <typename T>
void LinkedList<T>::display() const {
    if (!head) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node* current = head.get();
    while (current) {
        std::cout << current->data << (current->next ? " -> " : "\n");
        current = current->next.get();
    }
}

#endif // LINKED_LIST_H