#include <vector>
#include "BinaryOperation.h"

class Addition : public BinaryOperation {
public:
    Addition() {
        prior_lvl = 1;
        str = "+";
    }
    ~Addition() = default;

    double calculate(std::vector<double> nums) override {
        if (nums.size() != 2)
            throw -1;
            
        return nums[0] + nums[1];
    }
};