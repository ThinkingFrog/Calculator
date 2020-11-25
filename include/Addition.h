#include <vector>
#include "BaseOperation.h"

class Addition : public BaseOperation {
public:
    Addition() {
        type = op_type::binary;
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