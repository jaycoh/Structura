#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList();

    void insert(const T& data);
    void remove(const T& data);
    bool search(const T& data) const;
    void display() const;

    struct Node {
        T data;
        Node* next;
        Node* previous;
        Node(const T& value) : data(value), next(nullptr), previous(nullptr) {}
    };

    static void removeNode(Node* nodeToRemove, LinkedList<T>* list);

    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }

private:
    Node* head;
    Node* tail;
  
};

template <typename T>
void LinkedList<T>::removeNode(Node* nodeToRemove, LinkedList<T>* list) {
    if (!nodeToRemove) return;
    if (nodeToRemove->previous == nullptr) {
        list->head = nodeToRemove->next;
    } else {
        nodeToRemove->previous->next = nodeToRemove->next;
    }

    if (nodeToRemove->next == nullptr) {
        list->tail = nodeToRemove->previous;
    } else {
        nodeToRemove->next->previous = nodeToRemove->previous;
    }

    delete nodeToRemove;
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
    Node* newNode = new Node(data);
    newNode->data = data;
    newNode->next = head;
    newNode->previous = nullptr;

    if (head != nullptr) {
        head->previous = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;

}

template <typename T>
void LinkedList<T>::remove(const T& data) {
    Node* current = head;

    while (current != nullptr && current->data != data) {
        current = current->next;
    }

    if (current != nullptr) {
        removeNode(current, this);
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