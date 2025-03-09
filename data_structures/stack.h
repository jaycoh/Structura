#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
public:
    Stack() = default;
    ~Stack() = default;

    void push(const T& value);
    T pop();
    T top() const;
    bool empty() const;

private:
    std::vector<T> data{};
};
// By using defualt member initialization for all data members, we can avoid writing a constructor and destructor.

template <typename T>
void Stack<T>::push(const T& value) {
    // Since the parameter data is distinct, we (optionally) don't need to use this->data.
    data.push_back(value);
}

template <typename T>
T Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    T value = data.back();
    data.pop_back();
    return value;
}

template <typename T>
T Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return data.back();
}

template <typename T>
bool Stack<T>::empty() const {
    return data.empty();
}
#endif // STACK_H