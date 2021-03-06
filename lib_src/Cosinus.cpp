#include <vector>
#include <cmath>
#include "../include/BaseOperation.h"

class Cosinus : public BaseOperation {
public:
    Cosinus() {
        type = op_type::prefix;
        str = "cos";
    }
    ~Cosinus() = default;

    double calculate(std::vector<double> nums) override {
        if (nums.size() != 1)
            throw -1;
            
        return cos(nums[0]);
    }
};

extern "C" __declspec(dllexport) BaseOperation* LoadOperation() {
    BaseOperation* op = new Cosinus;
    return op;    
}
