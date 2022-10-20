#include <fstream>
#include <utility>
#include "Student.h"
#include "extern_function.h"

#include <iostream>

void copy_file_content(const char *file_1, const char *file_2) {
    using std::ios;
    using std::ifstream;
    using std::ofstream;
    ifstream in{file_1, ios::in};
    ofstream out{file_2, ios::out | ios::trunc};
    out << in.rdbuf();
    in.close();
    out.close();
}

Student create_student(std::string name, unsigned int age, unsigned int stuId) {
    return {std::move(name), age, stuId};
}

Student &input_student(std::istream &in, Student &student) {
    std::string name{};
    unsigned int age{};
    unsigned int id{};
    in >> name >> age >> id;
    student.setName(name);
    student.setAge(age);
    student.setStuId(id);
    return student;
}

void write_in_file(const char *file_name, const Student &student) {
    std::ofstream file{file_name, std::ios::app};
    file << student.getName() << " " << student.getAge() << " " << student.getStuId() << std::endl;
    file.close();
}

std::vector<Student> read_from_file(const char *file_name) {
    std::ifstream file{file_name, std::ios::in};
    std::string name{};
    std::vector<Student> arr{};
    unsigned int age{};
    unsigned int id{};
    while (file >> name >> age >> id) {
        if (file.eof()) {
            break;
        }
        arr.emplace_back(name, age, id);
    }
    file.close();
    return arr;
}

void homework_4_execute() {
    auto student0 = create_student("null", 0, 0);
    auto student1 = create_student("null", 0, 0);
    auto student2 = create_student("null", 0, 0);
    input_student(std::cin, student0);
    input_student(std::cin, student1);
    input_student(std::cin, student2);
    write_in_file("students.txt", student0);
    write_in_file("students.txt", student1);
    write_in_file("students.txt", student2);
    printf("---------------------------------------------------------\n");
    auto s = read_from_file("students.txt");
    for (const auto &i: s) {
        std::cout << i;
    }
}
