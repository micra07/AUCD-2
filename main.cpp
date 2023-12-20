#include <iostream>
#include <random>
#include <list.h>


int main() {


    LinkedList<Student> students;
    LinkedList<Student> tests(4);
    LinkedList<int> test;
    students.pop_head();

    test.push_tail(2);
    test.push_tail(1);
    test.push_tail(2);
    test.push_tail(2);
    test.push_tail(2);
    test.push_tail(3);
    test.push_tail(2);
    test.delete_node(2);
    for (size_t i = 0; i < test.get_size(); i++) {
        std::cout << test[i] << " " << std::endl;
    }

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
