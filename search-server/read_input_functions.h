#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "document.h"
#include "paginator.h"

std::string ReadLine();

int ReadLineWithNumber();

void PrintDocument(const Document& document);

std::ostream& operator<<(std::ostream& output, const Document& document);

template <typename Iterator>
std::ostream& operator<<(std::ostream& output, IteratorRange<Iterator> range) {
    for (auto it = range.begin(); it != range.end(); ++it) {
        output << *it; // *it - Document
    }
    return output;
}