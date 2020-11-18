#include <vector>
#include <cmath>
#include "../include/PostfixOperation.h"

class Factorial : public PostfixOperation {
public:
    Factorial() {
        str = "!";
    }
    ~Factorial() = default;

    double calculate(std::vector<double> nums) override {
        if (nums.size() != 1)
            throw -1;
        
        if (nums[0] == 0 || nums[0] == 1)
            return 1;

        double res = 1;

        for (unsigned i = 2; i <= round(nums[0]); ++i)
            res *= i;
            
        return res;
    }
};

extern "C" __declspec(dllexport) BaseOperation* LoadOperation() {
    BaseOperation* op = new Factorial;
    return op;    
}
