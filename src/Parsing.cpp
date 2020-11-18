#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "parsing.h"
#include "BaseOperation.h"

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

std::vector<std::string> toPolishNotation(const std::vector<std::string> &expr, const std::map<std::string, BaseOperation*> &operations) {
    std::vector<std::string> polish;
    std::deque<std::string> stack;

    for (std::string token : expr) {
        bool token_is_operation = operations.find(token) != operations.end();
        bool token_is_postfix = token_is_operation && operations.at(token)->get_type() == BaseOperation::op_type::postfix;
        bool token_is_prefix = token_is_operation && operations.at(token)->get_type() == BaseOperation::op_type::prefix;
        bool token_is_binary = token_is_operation && operations.at(token)->get_type() == BaseOperation::op_type::binary;
        bool stack_top_is_operation = !stack.empty() && operations.find(stack.front()) != operations.end();
        bool stack_top_is_prefix = stack_top_is_operation && operations.at(stack.front())->get_type() == BaseOperation::op_type::prefix;
        bool stack_prior_not_lower_than_token = stack_top_is_operation && token_is_operation && operations.at(stack.front())->priority() >= operations.at(token)->priority();

        if (stringIsDigit(token) || token_is_postfix) {
            polish.push_back(token);
        }
        else

        if (token_is_prefix || token == "(") {
            stack.push_front(token);
        }
        else

        if (token == ")") {
            if (!stack.empty())
                while (stack.front() != "(") {
                    polish.push_back(stack.front());
                    stack.pop_front();
                }
            stack.pop_front();
        }
        else

        if (token_is_operation && token_is_binary) {
            while (stack_top_is_prefix || stack_prior_not_lower_than_token) {
                polish.push_back(stack.front());
                stack.pop_front(); 

                stack_top_is_operation = !stack.empty() && operations.find(stack.front()) != operations.end();
                stack_top_is_prefix = stack_top_is_operation && operations.at(stack.front())->get_type() == BaseOperation::op_type::prefix;
                stack_prior_not_lower_than_token = stack_top_is_operation && token_is_operation && operations.at(stack.front())->priority() >= operations.at(token)->priority();
            }
            stack.push_front(token);
        }
        
        else {
            std::cout << "Unknown block in input string" << std::endl;
            break;
        }
    }

    for (std::string op : stack)
        polish.push_back(op);

    return polish;
}

double calculate(std::vector<std::string> polish, const std::map<std::string, BaseOperation*> &operations) {
    // count and erase elements of polish notation array until there is only one left
    while (polish.size() != 1) {
        unsigned i;
        // find index of first operation
        for (i = 0; i < polish.size(); ++i)
            if (!stringIsDigit(polish[i]))
                break;

        // determine operation
        BaseOperation* op = operations.at(polish[i]);

        // if binary operation, count with 2 operands
        if (op->get_type() == BaseOperation::op_type::binary) {
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
    return std::stod(polish.front());
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