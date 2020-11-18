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
    BaseOperation* add = new Addition;
    BaseOperation* mult = new Multiplication;
    std::map<std::string, BaseOperation*> operations = {{add->to_str(), add}, {mult->to_str(), mult}};
    std::vector<HMODULE> libraries;

    std::string plugins_dir = "../../plugins";
    for (auto plugin : fs::directory_iterator(plugins_dir)) {
        HMODULE lib = LoadLibraryA(plugin.path().string().c_str());
        LOADER loader = (LOADER)GetProcAddress(lib, "LoadOperation");
        
        BaseOperation* op = loader();
        operations[op->to_str()] = op;
        
        libraries.push_back(lib);
    }

    std::string expression;
    std::cout << "Input expression as single line:" << std::endl;
    std::getline(std::cin, expression);
    if (expression.empty())
        return 1;

    std::vector<std::string> splitted = split(expression, " ");
    std::vector<std::string> polish = toPolishNotation(splitted, operations);

    std::cout << calculate(polish, operations) << std::endl;
    
    for (HMODULE lib : libraries)
        FreeLibrary(lib);
    return 0;
}