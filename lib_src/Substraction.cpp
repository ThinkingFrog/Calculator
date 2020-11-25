#include <vector>
#include "../include/BaseOperation.h"

class Substraction : public BaseOperation {
public:
    Substraction() {
        type = op_type::binary;
        prior_lvl = 1;
        str = "-";
    }
    ~Substraction() = default;

    double calculate(std::vector<double> nums) override {
        if (nums.size() != 2)
            throw -1;
            
        return nums[0] - nums[1];
    }
};

extern "C" __declspec(dllexport) BaseOperation* LoadOperation() {
    BaseOperation* op = new Substraction;
    return op;    
}
