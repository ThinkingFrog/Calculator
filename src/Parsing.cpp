#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "parsing.h"
#include "BaseOperation.h"
#include "Context.h"

// split string by given delimeter
std::vector<std::string> split(const std::string &str, const std::string &delimeter) {
    size_t start = 0;
    size_t end = str.find(delimeter);

    std::vector<std::string> splitted;

    while (end != std::string::npos) {
        splitted.push_back(str.substr(start, end - start));
        start = end + delimeter.length();
        end = str.find(delimeter, start);
    }

    splitted.push_back(str.substr(start, end));

    return splitted;
}

// convert splitted string to polish notation to be fittable to calculations
int toPolishNotation(Context &context) {
    // iterate over splitted string
    for (std::string token : context.splitted) {
        // update context booleans used to make decisions while converting
        context.refresh_booleans(token);

        // if token is a number or a postfix operation - push it to output array
        if (stringIsDigit(token) || context.token_is_postfix) {
            context.polish.push_back(token);
        }
        else

        // if token is a prefix operation or an opening bracket - push it to stack
        if (context.token_is_prefix || token == "(") {
            context.stack.push_front(token);
        }
        else

        // if token is closing bracket - empty stack until we find corresponding opening bracket
        if (token == ")") {
            if (!context.stack.empty())
                while (context.stack.front() != "(") {
                    context.polish.push_back(context.stack.front());
                    context.stack.pop_front();
                }
            context.stack.pop_front();
        }
        else

        // if token is a binary operation - empty stack while it's top is a prefix operation or a binary with higher priority
        if (context.token_is_operation && context.token_is_binary) {
            while (context.stack_top_is_prefix || context.stack_prior_not_lower_than_token) {
                context.polish.push_back(context.stack.front());
                context.stack.pop_front(); 
                context.refresh_booleans(token);
            }
            context.stack.push_front(token);
        }
        
        // if token fits none of the above statements - consider it an error
        else {
            std::cout << "Unknown block in input string" << std::endl;
            return 1;
        }
    }

    // empty stack at the end
    for (std::string op : context.stack)
        context.polish.push_back(op);
    context.stack.clear();
    
    return 0;
}

// determine if string is positive, floating or negative number
bool stringIsDigit(const std::string &str) {
    if (str.empty())
        return false;

    if (str == "-")
        return false;

    for (char symb : str)
        if (!isdigit(symb) && symb != '.' && symb != '-')
            return false;

    return true;
}