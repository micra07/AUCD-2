// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <random>
#include <ctime>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    LinkedList(const LinkedList& other);
    LinkedList(int size);
    ~LinkedList();

 LinkedList& operator=(const LinkedList& other);

    void push_tail(const T& value);
    void push_tail(const LinkedList& otherList);
    void push_head(const T& value);
    void push_head(const LinkedList& otherList);
    void pop_head();
    void pop_tail();
    void delete_node(const T& value);

    T& operator[](int index);
    const T& operator[](int index) const;

private:
    Node<T>* head;
    Node<T>* tail;
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) {
    Node<T>* temp = other.head;
    while (temp != nullptr) {
        push_tail(temp->data);
        temp = temp->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(int size) : head(nullptr), tail(nullptr) {
    std::mt19937 mt(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<double> dist(1.0, 5.0);
    for (int i = 0; i < size; i++) {
        push_tail(dist(mt));
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        pop_head();
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this == &other) {
        return *this;
    }
    while (head != nullptr) {
        pop_head();
    }
    Node<T>* temp = other.head;
    while (temp != nullptr) {
        push_tail(temp->data);
        temp = temp->next;
    }
    return *this;
}

template <typename T>
void LinkedList<T>::push_tail(const T& value) {
    Node<T>* newNode = new Node<T>();
    newNode->data = value;
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T>
void LinkedList<T>::push_tail(const LinkedList& otherList) {
    Node<T>* temp = otherList.head;
    while (temp != nullptr) {
        push_tail(temp->data);
        temp = temp->next;
    }
}

template <typename T>
void LinkedList<T>::push_head(const T& value) {
    Node<T>* newNode = new Node<T>();
    newNode->data = value;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template <typename T>
void LinkedList<T>::push_head(const LinkedList& otherList) {
    Node<T>* temp = otherList.tail;
    while (temp != nullptr) {
        push_head(temp->data);
        temp = temp->prev;
    }
}

template <typename T>
void LinkedList<T>::pop_head() {
    if (head == nullptr) {
        return;
    }
    Node<T>* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete temp;
}

template <typename T>
void LinkedList<T>::pop_tail() {
    if (tail == nullptr) {
        return;
    }
    Node<T>* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete temp;
}

template <typename T>
void LinkedList<T>::delete_node(const T& value) {
    Node<T>* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            if (temp->prev == nullptr) {
                pop_head();
                temp = head;
            }
            else if (temp->next == nullptr) {
                pop_tail();
                temp = nullptr;
            }
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                Node<T>* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        else {
            temp = temp->next;
        }
    }
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
    Node<T>* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}

template <typename T>
const T& LinkedList<T>::operator[](int index) const {
    Node<T>* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;
}
