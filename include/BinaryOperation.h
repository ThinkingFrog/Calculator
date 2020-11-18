#pragma once
#include "BaseOperation.h"

class BinaryOperation : public BaseOperation {
public:
    BinaryOperation() {
        type = op_type::binary;
    }
    virtual ~BinaryOperation() = default;

};