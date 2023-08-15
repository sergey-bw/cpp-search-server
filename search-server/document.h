#pragma once

#include <iostream>
#include <string>

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

struct Document {
    Document();

    Document(int id_value, double relevance_value, int rating_value);

    int id = 0;
    double relevance = 0.0;
    int rating = 0;
};

void PrintDocument(const Document& document);

std::ostream& operator<<(std::ostream& output, const Document& document);