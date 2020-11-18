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

    op_type get_type() {
        return type;
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