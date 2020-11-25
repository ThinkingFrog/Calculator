#include <vector>
#include "BaseOperation.h"

class Multiplication : public BaseOperation {
public:
    Multiplication() {
        type = op_type::binary;
        prior_lvl = 2;
        str = "*";
    }
    ~Multiplication() = default;

    double calculate(std::vector<double> nums) override {
        if (nums.size() != 2)
            throw -1;

        return nums[0] * nums[1];
    }
};