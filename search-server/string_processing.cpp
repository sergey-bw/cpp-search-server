#include "string_processing.h"

std::vector<std::string> SplitIntoWords(const std::string& str) {
    std::vector<std::string> words;
    std::string word;
    for (const char c : str) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}