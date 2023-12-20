// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
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

template<typename T>
void LinkedList<T>::delete_node(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        if (current->data == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            else {
                tail = current->prev;
            }
            current = current->next;
            delete temp;
            size--;
        }
        else {
            current = current->next;
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



int main() {


    LinkedList<Student> students;
    LinkedList<Student> tests(4);


    students.push_tail({ "Ivanov", "Ivan", 3, 4.5 });
    students.push_tail({ "Romanov", "Nikolai", 1, 3.9 });
    students.push_tail({ "Panfilov", "Gleb", 4, 4.2 });
    students.push_tail({ "Kirillov", "Anton", 2, 2.2 });
    students.push_tail({ "Godunov", "Boris", 5, 5.0 });


    LinkedList<Student> seniorStudents1;
    LinkedList<Student> juniorStudents1;
    LinkedList<Student> seniorStudents2;
    LinkedList<Student> juniorStudents2;
    LinkedList<Student> tseniorStudents1;
    LinkedList<Student> tjuniorStudents1;


    for (size_t i = 0; i < tests.get_size(); i++) {
        if (tests[i].courseNumber > 2) {
            tseniorStudents1.push_tail(tests[i]);
        }
        else {
            tjuniorStudents1.push_tail(tests[i]);
        }
    }

    for (size_t i = 0; i < students.get_size(); i++) {
        if (students[i].courseNumber > 2) {
            seniorStudents1.push_tail(students[i]);
        }
        else {
            juniorStudents1.push_tail(students[i]);
        }
    }

    std::cout << "Senior:\n";
    for (size_t i = 0; i < seniorStudents1.get_size(); i++) {
        std::cout << seniorStudents1[i].lastName << " " << seniorStudents1[i].firstName << std::endl;
    }

    std::cout << "\nJunior:\n";
    for (size_t i = 0; i < juniorStudents1.get_size(); i++) {
        std::cout << juniorStudents1[i].lastName << " " << juniorStudents1[i].firstName << std::endl;
    }

    for (size_t i = 0; i < students.get_size(); i++) {
        if (students[i].courseNumber > 2) {
            seniorStudents2.push_tail(students[i]);
        }
        else {
            juniorStudents2.push_tail(students[i]);
        }
    }
   
    juniorStudents2.pop_head();
    std::cout << "\nJunior for pop_head:\n";
    for (size_t i = 0; i < juniorStudents2.get_size(); i++) {
        std::cout << juniorStudents2[i].lastName << " " << juniorStudents2[i].firstName << std::endl;
    }

    juniorStudents2.push_head({ "Dzhugashvili", "Joseph", 2, 4.8 });
    std::cout << "\nJunior for push_head:\n";
    for (size_t i = 0; i < juniorStudents2.get_size(); i++) {
        std::cout << juniorStudents2[i].lastName << " " << juniorStudents2[i].firstName << std::endl;
    }
    juniorStudents2.pop_tail();
    std::cout << "\nJunior for pop_tail:\n";
    for (size_t i = 0; i < juniorStudents2.get_size(); i++) {
        std::cout << juniorStudents2[i].lastName << " " << juniorStudents2[i].firstName << std::endl;
    }
    juniorStudents1.push_head(juniorStudents2);
    std::cout << "\nJunior for push_headlist:\n";
    for (size_t i = 0; i < juniorStudents1.get_size(); i++) {
        std::cout << juniorStudents1[i].lastName << " " << juniorStudents1[i].firstName << std::endl;
    }
    juniorStudents1.push_tail(juniorStudents2);
    std::cout << "\nJunior for push_taillist:\n";
    for (size_t i = 0; i < juniorStudents1.get_size(); i++) {
        std::cout << juniorStudents1[i].lastName << " " << juniorStudents1[i].firstName << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Tests:\n";
    for (size_t i = 0; i < tests.get_size(); i++) {
        std::cout << tests[i].lastName << " " << tests[i].firstName << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Tests Senior:\n";
    for (size_t i = 0; i < tseniorStudents1.get_size(); i++) {
        std::cout << tseniorStudents1[i].lastName << " " << tseniorStudents1[i].firstName << " " << tseniorStudents1[i].courseNumber << " " << tseniorStudents1[i].averageGrade << std::endl;
    }

    std::cout << "\nTests Junior:\n";
    for (size_t i = 0; i < tjuniorStudents1.get_size(); i++) {
        std::cout << tjuniorStudents1[i].lastName << " " << tjuniorStudents1[i].firstName << " " << tjuniorStudents1[i].courseNumber << " " << tjuniorStudents1[i].averageGrade << std::endl;
    }

    return 0;
}
