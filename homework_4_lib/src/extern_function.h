//
// Created by SoTTT on 2022/10/19.
//

#ifndef STL_HOMEWORKS_EXTERN_FUNCTION_H
#define STL_HOMEWORKS_EXTERN_FUNCTION_H

#include "Student.h"

void copy_file_content(const char *file_1, const char *file_2);
Student &input_student(std::istream &in, Student &student);
void write_in_file(const char *file_name, const Student &student);
std::vector<Student> read_from_file(const char *file_name);
Student create_student(std::string name, unsigned int age, unsigned int stuId);

void homework_4_execute();

#endif //STL_HOMEWORKS_EXTERN_FUNCTION_H
