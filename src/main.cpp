#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <map>
#include "Parsing.h"
#include "BaseOperation.h"
#include "Addition.h"
#include "Multiplication.h"

namespace fs = std::filesystem;

typedef BaseOperation* (*LOADER) ();

int main() {
    // Base functionality operations
    BaseOperation* add = new Addition;
    BaseOperation* mult = new Multiplication;
    // Dictionary that holds pairs of available operations and their string representations
    std::map<std::string, BaseOperation*> operations = {{add->to_str(), add}, {mult->to_str(), mult}};
    // Array of loaded dll libraries
    std::vector<HMODULE> libraries;

    // Dynamically link all libraries from given directory
    // Load dll libraries to array
    // Load operations from libraries to map dictionary
    fs::path plugins_dir("../../plugins");
    if (fs::exists(plugins_dir))
        for (auto plugin : fs::directory_iterator(plugins_dir)) {
            HMODULE lib = LoadLibraryA(plugin.path().string().c_str());
            LOADER loader = (LOADER)GetProcAddress(lib, "LoadOperation");
            
            BaseOperation* op = loader();
            operations[op->to_str()] = op;
            
            libraries.push_back(lib);
        }

    // Get input line from standard input
    std::string expression;
    std::cout << "Input expression as single line:" << std::endl;
    std::getline(std::cin, expression);
    if (expression.empty())
        return 1;

    // Split line to independent blocks by spacings
    std::vector<std::string> splitted = split(expression, " ");
    // Splitted blocks get reordered to form reverse polish notation
    std::vector<std::string> polish = toPolishNotation(splitted, operations);
    // Calculate reverse polish notation string and output result to standard output
    std::cout << calculate(polish, operations) << std::endl;
    
    // Unload libraries
    for (HMODULE lib : libraries)
        FreeLibrary(lib);
    return 0;
}