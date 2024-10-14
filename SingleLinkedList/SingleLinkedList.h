#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include <iostream>
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class SingleLinkedList {
public:
    SingleLinkedList();
    ~SingleLinkedList();

    T getCurrentVal() const;
    void setCurrentVal(const T& _val);
    bool isEmpty() const;
    void insert(T _val);
    void remove();
    void printList() const;

private:
    Node<T>* head;
    Node<T>* currentPos;
};

// Implementations

template<typename T>
SingleLinkedList<T>::SingleLinkedList() : head(nullptr), currentPos(nullptr) {}

template<typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    Node<T>* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
T SingleLinkedList<T>::getCurrentVal() const {
    if (currentPos == nullptr) {
        throw std::runtime_error("Empty current position! Can't get value!");
    }
    return currentPos->data;
}

template<typename T>
void SingleLinkedList<T>::setCurrentVal(const T& _val) {
    if (currentPos == nullptr) {
        throw std::runtime_error("Empty current position! Can't set value!");
    }
    currentPos->data = _val;
}

template<typename T>
bool SingleLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template<typename T>
void SingleLinkedList<T>::insert(T _val) {
    Node<T>* newNode = new Node<T>(_val);
    if (isEmpty()) {
        head = newNode;
        currentPos = head;
    } else {
        if (currentPos != nullptr) {
            newNode->next = currentPos->next;
            currentPos->next = newNode;
        }
    }
    currentPos = newNode;
}

template<typename T>
void SingleLinkedList<T>::remove() {
    if (currentPos == nullptr) {
        return;
    }
    if (currentPos->next == nullptr) {
        delete currentPos;
        currentPos = nullptr;
    } else {
        Node<T>* temp = currentPos->next;
        currentPos->next = temp->next;
        delete temp;
    }
}

template<typename T>
void SingleLinkedList<T>::printList() const {
    Node<T>* temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

#endif // SINGLELINKEDLIST_H
