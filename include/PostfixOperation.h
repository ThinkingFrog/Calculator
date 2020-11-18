#pragma once
#include "BaseOperation.h"

class PostfixOperation : public BaseOperation {
private:
public:
    PostfixOperation() {
        type = op_type::postfix;
    }
    virtual ~PostfixOperation() = default;
};