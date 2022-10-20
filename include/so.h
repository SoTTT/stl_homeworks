#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma once

#include <type_traits>
#include <iostream>
#include <stack>
#include <string>
#include <cassert>
#include <exception>
#include <cstring>
#include <cstdio>
#include <memory>
#include <algorithm>

namespace so {
    using std::void_t;
    using std::cout;
    using std::endl;

    template<typename T, typename V = void>
    struct is_printable : std::false_type {
    };

    template<typename T>
    struct is_printable<T, void_t<decltype(cout << T())>> : std::true_type {
    };

    namespace to_string_ns {
        template<typename T, typename char_t>
        std::basic_string<char_t> to_string(const T &value, const char *format = nullptr) {
            static_assert(sizeof(char_t) != sizeof(char_t), "This template cannot be instantiated");
            return std::basic_string<char_t>{};
        }

#define TO_STRING_FUNCTIONAL(TYPE) \
                template <> \
                inline std::string to_string<TYPE, std::string::value_type>(const TYPE & value, const char *format) \
                {            \
                    if (format==nullptr)\
                        return std::to_string(value);\
                    else {\
                        auto buffer = new char[100];\
                        sprintf(buffer, format, value);\
                        return std::string{buffer};\
                    }\
                }

        template<>
        inline std::string to_string<double, std::string::value_type>(const double &value, const char *format) {
            if (format == nullptr)
                return std::to_string(value);
            else {
                auto buffer = new char[100];
                sprintf(buffer, format, value);
                return std::string{buffer};
            }
        }

        template<>
        inline std::string
        to_string<std::string, std::string::value_type>(const std::string &value, const char *format) {
            return value;
        }

        TO_STRING_FUNCTIONAL(unsigned)

        TO_STRING_FUNCTIONAL(int)

        TO_STRING_FUNCTIONAL(long)

        TO_STRING_FUNCTIONAL(unsigned long)

        TO_STRING_FUNCTIONAL(long long)

        TO_STRING_FUNCTIONAL(unsigned long long)

        TO_STRING_FUNCTIONAL(float)

        TO_STRING_FUNCTIONAL(long double)
    }

    template<typename T, typename V = void>
    struct is_to_string_able : std::false_type {
    };

    template<typename T>
    struct is_to_string_able<T, void_t<decltype(to_string_ns::to_string<T, std::string::value_type>(T(), nullptr)
    )>> : std::true_type {
    };


    class no_argument_exception : public std::exception {
    public:
        no_argument_exception() = default;

        const char *message = "can't void_call this function with empty arguments list";

        const char *what() const noexcept override {
            return message;
        }
    };


    class arguments_no_match_exception : public std::exception {
    public:
        arguments_no_match_exception() = default;

        const char *message = "the braces are not match to very argument package";

        const char *what() const noexcept override {
            return message;
        }
    };

    inline size_t println() {
        throw no_argument_exception();
    }

    template<typename T>
    size_t println(T value) noexcept(noexcept(cout << value << endl)) {
        static_assert(is_printable<T>::value, R"(assert: the object of type "T" not override operator "<<")");
        cout << value << endl;
        return 1;
    }

    template<typename T, typename ...Args>
    size_t println(T value, Args ... args) noexcept(noexcept(cout << value)) {
        static_assert(is_printable<T>::value, R"(assert: the object of type "T" not override operator "<<")");
        cout << value;
        println(args...);
        return sizeof...(args) + 1;
    }

    namespace format_impl {
        std::string take_format_pattern_for_sprintf(const char *format, size_t len) noexcept {
            if (format == nullptr || len <= 0) {
                return {};
            }
            long position = -1;
            for (auto i = 0u; i < len; ++i) {
                if (format[i] == ':')
                    position = static_cast<long>(i);
            }
            if (position != -1) {
                char array[100];
                std::strcpy(array, format + 1 + position);
                array[len - position - 2] = '\0';
                return {array};
            } else {
                return {};
            }
        }

        template<typename char_t, typename T, typename ...Args>
        std::basic_string<char_t> format(std::basic_string<char_t> raw_string, T value) {
            static_assert(is_to_string_able<T>::value,
                          R"(the type "T" has functional or callable object "to_string<T>")");
            typename std::basic_string<char_t>::size_type begin_of_find_left = 0;
            typename std::basic_string<char_t>::size_type begin_of_find_right = 0;
            typename std::basic_string<char_t>::size_type first_left = 0;
            typename std::basic_string<char_t>::size_type first_right = 0;
            do {
                first_left = raw_string.find_first_of("{", begin_of_find_left);
            } while (first_left != std::basic_string<char_t>::npos &&
                     (first_left != 0
                      ? (raw_string[first_left - 1] == '\\' && (begin_of_find_left = first_left + 1, true))
                      : false));
            do {
                first_right = raw_string.find_first_of("}", begin_of_find_right);
            } while (first_right != std::basic_string<char_t>::npos &&
                     (first_right != 0
                      ? (raw_string[first_right - 1] == '\\' &&
                         (begin_of_find_right = first_right + 1, true))
                      : false));
            if (first_left != std::basic_string<char_t>::npos && first_right != std::basic_string<char_t>::npos &&
                first_left < first_right && raw_string[first_left - 1] != '\\'
                &&
                raw_string[first_right - 1] != '\\') {
                auto format_p = take_format_pattern_for_sprintf(raw_string.c_str() + first_left + 1,
                                                                first_right - first_left);
                auto p = format_p.c_str();
                if (format_p.size() == 0) {
                    p = nullptr;
                }
                raw_string.replace(first_left, first_right - first_left + 1,
                                   to_string_ns::to_string<T, char_t>(value, p));
            } else {
                throw arguments_no_match_exception();
            }
            return raw_string;
        }

        template<typename char_t, typename T, typename ...Args>
        std::basic_string<char_t> format(std::basic_string<char_t> raw_string, T value, Args ... args) {
            static_assert(is_to_string_able<T>::value,
                          R"(the type "T" has functional or callable object "to_string<T>")");
            typename std::basic_string<char_t>::size_type begin_of_find_left = 0;
            typename std::basic_string<char_t>::size_type begin_of_find_right = 0;
            typename std::basic_string<char_t>::size_type first_left = 0;
            typename std::basic_string<char_t>::size_type first_right = 0;
            do {
                first_left = raw_string.find_first_of("{", begin_of_find_left);
            } while (first_left != std::basic_string<char_t>::npos &&
                     (first_left != 0
                      ? (raw_string[first_left - 1] == '\\' && (begin_of_find_left = first_left + 1, true))
                      : false));
            do {
                first_right = raw_string.find_first_of("}", begin_of_find_right);
            } while (first_right != std::basic_string<char_t>::npos &&
                     (first_right != 0
                      ? (raw_string[first_right - 1] == '\\' &&
                         (begin_of_find_right = first_right + 1, true))
                      : false));
            if (first_left != std::basic_string<char_t>::npos && first_right != std::basic_string<char_t>::npos &&
                first_left < first_right) {
                auto format_p = take_format_pattern_for_sprintf(raw_string.c_str() + first_left + 1,
                                                                first_right - first_left);
                auto p = format_p.c_str();
                if (format_p.size() == 0) {
                    p = nullptr;
                }
                raw_string.replace(first_left, first_right - first_left + 1,
                                   to_string_ns::to_string<T, char_t>(value, p));
            } else {
                throw arguments_no_match_exception();
            }
            return format(raw_string, args...);
        }
    }


    template<typename char_t, typename ...Args>
    std::basic_string<char_t> format(std::basic_string<char_t> &raw_string, Args ... args) {
        if (sizeof...(args) == 0) {
            throw no_argument_exception();
        }
        try {
            auto result_string = format_impl::format(raw_string, args...);
            while (result_string.find("\\{") != std::basic_string<char_t>::npos) {
                result_string.replace(result_string.find_first_of("\\{"), 2, {"{"});
            }
            while (result_string.find("\\}") != std::basic_string<char_t>::npos) {
                result_string.replace(result_string.find_first_of("\\}"), 2, {"}"});
            }
            return result_string;
        }
        catch (const arguments_no_match_exception &e) {
            throw e;
        }
    }
}

#pragma clang diagnostic pop
