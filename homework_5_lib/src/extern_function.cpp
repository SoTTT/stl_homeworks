//
// Created by SoTTT on 2022/11/2.
//

#include "extern_function.h"
#include <algorithm>

using std::cout;
using std::endl;

vector<string> read_and_spilt(const char *filename) {
    std::ifstream in{};
    string str;
    vector<string> arr;
    in.open(filename);
    if (in) {
        std::getline(in, str);
        auto it_p = 0;
        auto it = it_p + 1;
        auto end = str.length();
        while (it < end && it_p < end) {
            if (!std::isalnum(str[it]) || it == end) {
                auto temp = str.substr(it_p, it - it_p);
                arr.push_back(std::move(temp));
                it_p = it + 1;
                it = it_p + 1;
                continue;
            }
            ++it;
        }
        return arr;
    }
    return arr;
}

void basic_string_operate() {
    //constructs a basic_string
    string str{"the practice operation is try to use basic_string methods"};
    auto sub = str.substr(0, 11);
    cout << "substr of str position from 0 to 11 :" << sub << endl;
    auto pos = str.find("use");
    cout << "the position of word \"the\" in str is :" << pos << endl;
    auto size = str.length();
    cout << "the length of str is :" << size << endl;
    auto max_size = str.max_size();
    cout << "the max length(not need reallocate memory) of str is :" << max_size << endl;
    auto new_str = str.append("2022");
    cout << "append string to tail of str :" << new_str << endl;
    new_str = str.insert(5, "ssss");
    cout << "insert string in str:" << new_str << endl;
    new_str = str;
    //new_str.erase(std::remove(str.begin(), str.end(), 'a'), new_str.end());
    cout << "remove all 'a' character in str: " << new_str << endl;
}

void homework_5_execute() {
    auto arr = read_and_spilt("a.txt");
    for (const auto &i: arr) {
        cout << i << endl;
    }
    basic_string_operate();
}
