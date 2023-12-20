#include <iostream>
#include <random>


struct Student {
    std::string lastName;
    std::string firstName;
    int courseNumber;
    double averageGrade;
};


template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList(size_t count);
    LinkedList& operator=(const LinkedList& other);
    ~LinkedList();
    void push_tail(const T& value);
    void push_tail(const LinkedList& other);
    void push_head(const T& value);
    void push_head(const LinkedList& other);
    void pop_head();
    void pop_tail();
    void delete_node(const T& value);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t get_size() const;
};

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : LinkedList() {
    Node* current = other.head;
    while (current != nullptr) {
        push_tail(current->data);
        current = current->next;
    }
}

template<typename T>
LinkedList<T>::LinkedList(size_t count) : LinkedList() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> lastNameDist(0, 25);
    std::uniform_int_distribution<int> firstNameDist(0, 25);
    std::uniform_int_distribution<int> courseNumberDist(1, 5);
    std::uniform_real_distribution<double> averageGradeDist(2.0, 5.0);

    for (size_t i = 0; i < count; i++) {
        std::string lastName = "";
        for (int j = 0; j < 6; j++) {
            lastName += char('A' + lastNameDist(gen));
        }

        std::string firstName = "";
        for (int j = 0; j < 6; j++) {
            firstName += char('A' + firstNameDist(gen));
        }

        int courseNumber = courseNumberDist(gen);
        double averageGrade = averageGradeDist(gen);

        Student student{ lastName, firstName, courseNumber, averageGrade };
        push_tail(student);
    }
}



template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        LinkedList<T> temp(other);
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(size, temp.size);
    }
    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::push_tail(const T& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
    }
    tail = newNode;
    size++;
}

template<typename T>
void LinkedList<T>::push_tail(const LinkedList& other) {
    Node* current = other.head;
    while (current != nullptr) {
        push_tail(current->data);
        current = current->next;
    }
}

template<typename T>
void LinkedList<T>::push_head(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        tail = newNode;
    }
    else {
        head->prev = newNode;
        newNode->next = head;
    }
    head = newNode;
    size++;
}

template<typename T>
void LinkedList<T>::push_head(const LinkedList& other) {
    Node* current = other.tail;
    while (current != nullptr) {
        push_head(current->data);
        current = current->prev;
    }
}

template<typename T>
void LinkedList<T>::pop_head() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }
}

template<typename T>
void LinkedList<T>::pop_tail() {
    if (tail != nullptr) {
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        size--;
    }
}

//template<typename T>
//void LinkedList<T>::delete_node(const T& value) {
//    Node* current = head;
//    while (current != nullptr) {
//        Node* temp = current;
//        current = current->next;
//        if (temp->data == value) {
//            if (temp == head) {
//                head = temp->next;
//                if (head != nullptr) {
//                    head->prev = nullptr;
//                }
//            }
//            if (temp == tail) {
//                tail = temp->prev;
//                if (tail != nullptr) {
//                    tail->next = nullptr;
//                }
//            }
//            if (temp->prev != nullptr) {
//                temp->prev->next = temp->next;
//            }
//            if (temp->next != nullptr) {
//                temp->next->prev = temp->prev;
//            }
//            delete temp;
//            size--;
//        }
//    }
//}
template<typename T>
void LinkedList<T>::delete_node(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        if (temp->data == value) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            else {
                head = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
            else {
                tail = temp->prev;
            }
            delete temp;
            size--;
        }
    }
}

template<typename T>
T& LinkedList<T>::operator[](size_t index) {
    Node* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
const T& LinkedList<T>::operator[](size_t index) const {
    Node* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
size_t LinkedList<T>::get_size() const {
    return size;
}
