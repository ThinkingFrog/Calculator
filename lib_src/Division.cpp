#include <vector>
#include "../include/BinaryOperation.h"

class Division : public BinaryOperation {
public:
    Division() {
        prior_lvl = 2;
        str = "/";
    }
    ~Division() = default;

    double calculate(std::vector<double> nums) override {
        if (nums.size() != 2)
            throw -1;
            
        return nums[0] / nums[1];
    }
};

extern "C" __declspec(dllexport) BaseOperation* LoadOperation() {
    BaseOperation* op = new Division;
    return op;    
}
