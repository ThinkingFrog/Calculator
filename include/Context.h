#pragma once
#include <filesystem>
#include <vector>
#include <windows.h>
#include <map>
#include <string>
#include <deque>
#include "BaseOperation.h"

namespace fs = std::filesystem;

// Run context structure that holds all properties of application used in various places
struct Context {
    // essential fields that operate with plugins and available mathematical operations
    fs::path plugins_dir;
    std::vector<HMODULE> libraries;
    std::map<std::string, BaseOperation*> operations;

    // fields that represent input expression and its different forms
    std::string expression;
    std::vector<std::string> splitted;
    std::vector<std::string> polish;
    std::deque<std::string> stack;
    double result;

    // temporary booleans used in polish notation procedure
    bool token_is_operation;
    bool token_is_postfix;
    bool token_is_prefix;
    bool token_is_binary;
    bool stack_top_is_operation;
    bool stack_top_is_prefix;
    bool stack_prior_not_lower_than_token;
    
    Context() = default;
    Context(const fs::path &plugins_dir) {
        this->plugins_dir = plugins_dir;
    }
    Context(fs::path &&plugins_dir) {
        this->plugins_dir = std::move(plugins_dir);
    }

    ~Context() {
        // Unload libraries
        for (HMODULE lib : libraries)
            FreeLibrary(lib);
    }

    void refresh_booleans(std::string token) {
        token_is_operation = operations.find(token) != operations.end();
        token_is_postfix = token_is_operation && operations.at(token)->is_postfix();
        token_is_prefix = token_is_operation && operations.at(token)->is_prefix();
        token_is_binary = token_is_operation && operations.at(token)->is_binary();
        stack_top_is_operation = !stack.empty() && operations.find(stack.front()) != operations.end();
        stack_top_is_prefix = stack_top_is_operation && operations.at(stack.front())->is_prefix();
        stack_prior_not_lower_than_token = stack_top_is_operation && token_is_operation
        && operations.at(stack.front())->priority() >= operations.at(token)->priority();
    }
};