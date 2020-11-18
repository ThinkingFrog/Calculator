#pragma once
#include "BaseOperation.h"

class PrefixOperation : public BaseOperation {
private:
public:
    PrefixOperation() {
        type = op_type::prefix;
    }
    virtual ~PrefixOperation() = default;
};