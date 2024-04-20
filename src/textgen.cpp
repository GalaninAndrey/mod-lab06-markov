// Copyright 2024 Galanin Andrey
#include <fstream>
#include <random>
#include <functional>
#include "../include/textgen.h"
#include <iostream>
#include <random>

void GenerationText::Learn(std::string& string, int size) { 
    std::istringstream text(string);
    prefix prefix;
    std::string word;
    for (int i = 0; i < size; i++) {
        text >> word;
        prefix.push_back(word);
    }
    fprefix = prefix;
    while (text >> word) {
        statetab[prefix].push_back(word);
        prefix.pop_front();
        prefix.push_back(word);
    }
}

std::string GenerationText::Create(int length, int seed, int size) {
    if (seed == 0) seed = time(0);
    std::default_random_engine generation(seed);

    prefix CurPref = fprefix;
    std::string string;
    for (auto it = CurPref.begin(); it != CurPref.end(); ++it) {
        string += *it + " ";
    }

    while (string.size() < length) {
        if (statetab[CurPref].empty()) break;
        std::uniform_int_distribution<> dist(0, statetab[CurPref].size() - 1);
        std::string suffix = statetab[CurPref][dist(generation)];
        string += suffix + " ";
        CurPref.pop_front();
        CurPref.push_back(suffix);
    }
    return string;
}
void GenerationText::set(std::map<prefix, std::vector<std::string>> string) {
    statetab = string;
}

std::map<prefix, std::vector<std::string>> GenerationText::get() {
   return statetab;
}