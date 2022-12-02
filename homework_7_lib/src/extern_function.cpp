//
// Created by SoTTT on 2022/11/29.
//

#include "extern_function.h"
#include <cmath>
#include <iostream>
#include "so.h"

Complex::Complex(const int arg_i, const int arg_j) : m_i(arg_i), m_j(arg_j) {

}

Complex operator+(const Complex &_1, const Complex &_2) {
    return Complex{_1.m_i + _2.m_i, _2.m_j + _1.m_j};
}

std::string Complex::to_string() const {
    return so::format("Complex({}i+{}j)", m_i, m_j);
}

void homework_7_execute() {
    Complex complex1(1, 2);
    Complex complex2(4, 3);
    std::cout << "first complex is :" << complex1.to_string() << std::endl;
    std::cout << "second complex is :" << complex2.to_string() << std::endl;
    std::plus<Complex> plus;
    std::cout << "sum of complex1 and complex2 is :" << plus(complex1, complex2).to_string() << std::endl;
    Triangle triangle(3, 4, 5);
    std::cout << "area of " << triangle.to_string() << " is " << std::to_string(triangle.evalArea()) << std::endl;
    Square square(4);
    std::cout << "area of " << square.to_string() << " is " << std::to_string(square.evalArea()) << std::endl;
}

double Square::evalArea() {
    return m_edge * m_edge;
}

Square::Square(const double &edge) : m_edge(edge) {

}

std::string Square::to_string() {
    return so::format("Square(edge={})", m_edge);
}

double Triangle::evalArea() {
    double p = (m_a + m_b + m_c) / 2;
    return std::sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
}

Triangle::Triangle(const double &a, const double &b, const double &c) : m_a(a), m_b(b), m_c(c) {

}

std::string Triangle::to_string() {
    return so::format("Triangle(a={},b={},c={});", m_a, m_b, m_c);
}
