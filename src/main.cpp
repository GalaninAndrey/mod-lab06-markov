// Copyright 2024 Galanin Andrey
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "../include/textgen.h"
const int NPREF = 2;
const int MAXGEN = 100;

int main() {
    std::string string;
    std::string line;
    std::ifstream input("text.txt");
    while (std::getline(input, line)) {
        string += line + " ";
    }
    GenerationText generationtext;
    generationtext.Learn(string, NPREF);
    std::cout << generationtext.Create(MAXGEN, 20);
    return 0;
}
