//
// Created by SoTTT on 2022/11/29.
//

#ifndef STL_HOMEWORKS_EXTERN_FUNCTION_H
#define STL_HOMEWORKS_EXTERN_FUNCTION_H

#include <algorithm>
#include <string>

class Complex {
    int m_i = 0;
    int m_j = 0;
public:
    Complex(int arg_i, int arg_j);

    Complex() = default;

    friend Complex operator+(const Complex &_1, const Complex &_2);

    std::string to_string() const;

};

class Shape {
public:
    virtual double evalArea() = 0;

    virtual std::string to_string() = 0;
};

class Square : public Shape {
    double m_edge = 0;
public:
    Square(const double &edge);

    double evalArea() override;

    std::string to_string() override;
};

class Triangle : public Shape {
    double m_a = 0;
    double m_b = 0;
    double m_c = 0;
public:
    Triangle(const double &, const double &, const double &);

    std::string to_string() override;

    double evalArea() override;
};


void homework_7_execute();


#endif //STL_HOMEWORKS_EXTERN_FUNCTION_H
