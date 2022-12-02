//
// Created by SoTTT on 2022/11/16.
//

#ifndef STL_HOMEWORKS_EXTERN_FUNCTION_H
#define STL_HOMEWORKS_EXTERN_FUNCTION_H

#include <vector>

class FunctionalPower {

public:
    double operator()(const std::vector<int> &vector, unsigned pow, double init) const;

};

void homework_5_execute();


#endif //STL_HOMEWORKS_EXTERN_FUNCTION_H
