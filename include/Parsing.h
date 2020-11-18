#pragma once
#include <string>
#include <vector>
#include "BaseOperation.h"

std::vector<std::string> split(const std::string& str, const std::string& delimeter);
std::vector<std::string> toPolishNotation(const std::vector<std::string> &expr, const std::map<std::string, BaseOperation*> &operations);
double calculate(std::vector<std::string> polish, const std::map<std::string, BaseOperation*> &operations);
bool stringIsDigit(const std::string &str);