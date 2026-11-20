#pragma once

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

// std::pair
template <typename First, typename Second>
std::ostream& operator<<(std::ostream& output, const std::pair<First, Second>& p) {
    output << "(" << p.first << ", " << p.second << ")";
    return output;
}

template <typename Container>
std::ostream& PrintContainer(std::ostream& output, const Container& container,
                            char open, char close) {
    output << open;
    bool first_item = true;
    for (const auto& item : container) {
        if (!first_item) output << ", ";
        output << item;
        first_item = false;
    }
    output << close;
    return output;
}

// std::vector
template <typename T, typename Alloc>
std::ostream& operator<<(std::ostream& output, const std::vector<T, Alloc>& c) {
    return PrintContainer(output, c, '[', ']');
}

// std::array
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& output, const std::array<T, N>& c) {
    return PrintContainer(output, c, '[', ']');
}

// std::set
template <typename T, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& output, const std::set<T, Compare, Alloc>& c) {
    return PrintContainer(output, c, '{', '}');
}

// std::unordered_set
template <typename T, typename Hash, typename KeyEqual, typename Alloc>
std::ostream& operator<<(std::ostream& output, const std::unordered_set<T, Hash, KeyEqual, Alloc>& c) {
    return PrintContainer(output, c, '{', '}');
}

// std::map
template <typename Key, typename Value, typename Compare, typename Alloc>
std::ostream& operator<<(std::ostream& output, const std::map<Key, Value, Compare, Alloc>& c) {
    return PrintContainer(output, c, '{', '}');
}

// std::unordered_map
template <typename Key, typename Value, typename Hash, typename KeyEqual, typename Alloc>
std::ostream& operator<<(std::ostream& output, const std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>& c) {
    return PrintContainer(output, c, '{', '}');
}

void LogImpl(const std::string& str, const std::string& func_name , const std::string& file_name, int line_number) {
    std::cerr << file_name << "(" << line_number << "): ";
    std::cerr << func_name << ": " << str << std::endl;
}

#define LOG(expr) LogImpl(#expr, __FUNCTION__, __FILE__, __LINE__)

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const std::string& t_str, const std::string& u_str, const std::string& file
                    , const std::string& func, unsigned line, const std::string& hint = "")
{
    if (t != u) {
        std::cerr << std::boolalpha;
        std::cerr << file << "(" << line << "): " << func << ": ";
        std::cerr << "ASSERT_EQUAL(" << t_str << ", " << u_str << ") failed: ";
        std::cerr << t << " != " << u << ".";
        if (!hint.empty()) {
            std::cerr << " Hint: " << hint;
        }
        std::cerr << std::endl;
        abort();
    }
}

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

void AssertImpl(bool value, const std::string& expr_str, const std::string& file, const std::string& func, unsigned line,
                const std::string& hint = "") {
    if (!value) {
        std::cerr << file << "(" << line << "): " << func << ": ";
        std::cerr << "Assert(" << expr_str << ") failed.";
        if (!hint.empty()) {
            std::cerr << " Hint: " << hint;
        }
        std::cerr << std::endl;
        abort();
    }
}

#define ASSERT(a) AssertImpl((a), #a, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_HINT(a, hint) AssertImpl((a), #a, __FILE__, __FUNCTION__, __LINE__, (hint))

template <typename TestFunc>
void RunTestImpl(const TestFunc& func, const std::string& test_name) {
    func();
    std::cerr << test_name << " OK" << std::endl;
}

#define RUN_TEST(func) RunTestImpl(func, #func) 