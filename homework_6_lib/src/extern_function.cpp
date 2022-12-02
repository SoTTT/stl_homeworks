//
// Created by SoTTT on 2022/11/16.
//
#include "extern_function.h"
#include <cmath>
#include <iostream>

double FunctionalPower::operator()(const std::vector<int> &vector, unsigned int pow, double init) const {
    for (const auto &item: vector)
        init += std::pow((double) item, (double) pow);
    return init;
}


void homework_5_execute() {
    std::vector<int> vector{1, 2, 3, 4, 5};
    FunctionalPower fun{};
    double v = fun(vector, 2, 0);
    std::cout << v << std::endl;
}
