#include <iostream>
#include <windows.h>
#include <map>
#include <string>
#include "BaseOperation.h"
#include "Addition.h"
#include "Multiplication.h"
#include "SupportModule.h"
#include "Context.h"
#include "Parsing.h"

int loadPlugins(Context &context) {
    // Base functionality operations
    BaseOperation* add = new Addition;
    BaseOperation* mult = new Multiplication;

    context.operations[add->to_str()] = add;
    context.operations[mult->to_str()] = mult;

    if (fs::exists(context.plugins_dir))
        for (auto plugin : fs::directory_iterator(context.plugins_dir)) {
            HMODULE lib = LoadLibraryA(plugin.path().string().c_str());
            if (GetLastError() != 0)
                return GetLastError();

            LOADER loader = (LOADER)GetProcAddress(lib, "LoadOperation");
            if (GetLastError() != 0)
                return GetLastError();
            
            BaseOperation* op = loader();
            context.operations[op->to_str()] = op;
            
            context.libraries.push_back(lib);
        }

    return 0;
}

int getExpression(Context &context) {
    // Get input line from standard input
    std::cout << "Input expression as single line:" << std::endl;
    std::getline(std::cin, context.expression);

    if (context.expression.empty())
        return 1;
    
    return 0;
}

int operateExpression(Context &context) {
    // Split line to independent blocks by spacings
    context.splitted = split(context.expression, " ");
    // Splitted blocks get reordered to form reverse polish notation
    if (toPolishNotation(context) != 0)
        return 1;
    // Calculate reverse polish notation string and save it to context field
    if (calculate(context) != 0)
        return 2;

    return 0;
}

int calculate(Context &context) {
    // make a copy to leave polish notation string in context unmodified
    std::vector<std::string> polish = context.polish;
    // count and erase elements of polish notation array until there is only one left
    while (polish.size() != 1) {
        unsigned i;
        // find index of first operation
        for (i = 0; i < polish.size(); ++i)
            if (!stringIsDigit(polish[i]))
                break;

        // determine operation
        BaseOperation* op = context.operations.at(polish[i]);

        // if binary operation, count with 2 operands
        if (op->is_binary()) {
            double res = op->calculate({std::stod(polish[i - 2]), std::stod(polish[i - 1])});
            polish[i - 2] = std::to_string(res);
            polish.erase(polish.begin() + i - 1);
            polish.erase(polish.begin() + i - 1);
        }
        // if unary, count with 1 operand
        else {
            double res = op->calculate({std::stod(polish[i - 1])});
            polish[i - 1] = std::to_string(res);
            polish.erase(polish.begin() + i);
        }
    }

    context.result = std::stod(polish.front());
    return 0;
}