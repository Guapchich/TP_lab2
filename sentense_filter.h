#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <string>
#include <regex>

using namespace std;

class SentenceFilter {
private:
    string source;
    bool isTextSource;

    void split_into_lines(const string& text, string*& lines, int& lineCount) const;
    string swap_adjacent_words(const string& line) const;

public:
    SentenceFilter();
    SentenceFilter(const string& filename);
    SentenceFilter(const string& text, bool isText);
    SentenceFilter(const SentenceFilter& other);
    ~SentenceFilter();
    void result() const;
};
