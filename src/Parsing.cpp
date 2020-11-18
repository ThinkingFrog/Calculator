#include <string>
#include <vector>
#include <deque>
#include <map>
#include "parsing.h"
#include "BaseOperation.h"

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
        if (stringIsDigit(token) || 
        (operations.find(token) != operations.end() && operations.at(token)->get_type() == BaseOperation::op_type::postfix)) {
            polish.push_back(token);
            continue;
        }

        if ((operations.find(token) != operations.end() && operations.at(token)->get_type() == BaseOperation::op_type::prefix)
        || token == "(") {
            stack.push_front(token);
            continue;
        }

        if (token == ")") {
            if (!stack.empty())
                while (stack.front() != "(") {
                    polish.push_back(stack.front());
                    stack.pop_front();
                }
            stack.pop_front();
            continue;
        }

        if (operations.find(token) != operations.end() && operations.at(token)->get_type() == BaseOperation::op_type::binary) {
            if (!stack.empty()) {
                while (!stack.empty() && operations.find(stack.front()) != operations.end() && operations.find(token) != operations.end() &&
                (operations.at(stack.front())->get_type() == BaseOperation::op_type::prefix ||
                operations.at(stack.front())->priority() >= operations.at(token)->priority())) {
                    polish.push_back(stack.front());
                    stack.pop_front(); 
                }
            }
            stack.push_front(token);
            continue;
        }
    }

    for (std::string op : stack)
        polish.push_back(op);

    return polish;
}

double calculate(std::vector<std::string> polish, const std::map<std::string, BaseOperation*> &operations) {
    while (polish.size() != 1) {
        unsigned i;
        for (i = 0; i < polish.size(); ++i)
            if (!stringIsDigit(polish[i]))
                break;

        BaseOperation* op = operations.at(polish[i]);

        if (op->get_type() == BaseOperation::op_type::binary) {
            double res = op->calculate({std::stod(polish[i - 2]), std::stod(polish[i - 1])});
            polish[i - 2] = std::to_string(res);
            polish.erase(polish.begin() + i - 1);
            polish.erase(polish.begin() + i - 1);
        }
        else {
            double res = op->calculate({std::stod(polish[i - 1])});
            polish[i - 1] = std::to_string(res);
            polish.erase(polish.begin() + i);
        }
    }
    return std::stod(polish.front());
}

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