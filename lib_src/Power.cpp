#include <vector>
#include <cmath>
#include "../include/BaseOperation.h"

class Power : public BaseOperation {
public:
    Power() {
        type = op_type::binary;
        prior_lvl = 3;
        str = "^";
    }
    ~Power() = default;

    double calculate(std::vector<double> nums) override {
        if (nums.size() != 2)
            throw -1;
            
        return pow(nums[0], nums[1]);
    }
};

extern "C" __declspec(dllexport) BaseOperation* LoadOperation() {
    BaseOperation* op = new Power;
    return op;    
}
