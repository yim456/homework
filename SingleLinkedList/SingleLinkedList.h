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

#endif // SINGLELINKEDLIST_H
