#ifndef STL_HOMEWORKS_STUDENT_H
#define STL_HOMEWORKS_STUDENT_H


#include <string>
#include <utility>
#include <vector>

class Student {

private:
    std::string _name;
    unsigned _age;
    unsigned _stu_id;
public:
    const std::string &getName() const;

    unsigned int getAge() const;

    unsigned int getStuId() const;

public:
    void setName(const std::string &name);

    void setAge(unsigned int age);

    void setStuId(unsigned int stuId);

public:
    Student(std::string name, unsigned int age, unsigned int stuId);

    virtual ~Student();

    friend std::ostream& operator<<(std::ostream &out, const Student &student);
};

std::ostream& operator<<(std::ostream &out, const Student &student);


#endif //STL_HOMEWORKS_STUDENT_H
