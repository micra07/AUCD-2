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
