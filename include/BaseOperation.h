#pragma once
#include <vector>
#include <string>

class BaseOperation {
public:
    enum op_type {
        postfix,
        prefix,
        binary
    };
    BaseOperation() = default;
    virtual ~BaseOperation() = default;

    std::string to_str() {
        return str;
    }

    bool is_postfix() {
        return type == op_type::postfix;
    }
    bool is_prefix() {
        return type == op_type::prefix;
    }
    bool is_binary() {
        return type == op_type::binary;
    }

    unsigned short priority() {
        return prior_lvl;
    }

    virtual double calculate(std::vector<double> nums) = 0;
protected:
    // string representation
    std::string str;
    // type of operation coresponding to base class it's derived from
    op_type type;
    // level of priority for binary operations
    // 1 level is the lowest
    unsigned short prior_lvl;
};