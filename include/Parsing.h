#pragma once
#include <string>
#include <vector>
#include "BaseOperation.h"
#include "Context.h"

std::vector<std::string> split(const std::string& str, const std::string& delimeter);
int toPolishNotation(Context &context);
bool stringIsDigit(const std::string &str);