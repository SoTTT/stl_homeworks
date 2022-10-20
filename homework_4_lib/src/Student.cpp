#include "Student.h"
#include "so.h"

Student::Student(std::string name, unsigned int age, unsigned int stuId) : _name(std::move(name)), _age(age),
                                                                           _stu_id(stuId) {}

Student::~Student() = default;

std::ostream& operator<<(std::ostream &out, const Student &student) {
    std::string raw{"name: {}\n age: {}\n student id: {}\n"};
    out << so::format(raw, student._name, student._age, student._stu_id);
    return out;
}

void Student::setName(const std::string &name) {
    _name = name;
}

void Student::setAge(unsigned int age) {
    _age = age;
}

void Student::setStuId(unsigned int stuId) {
    _stu_id = stuId;
}

const std::string &Student::getName() const {
    return _name;
}

unsigned int Student::getAge() const {
    return _age;
}

unsigned int Student::getStuId() const {
    return _stu_id;
}

