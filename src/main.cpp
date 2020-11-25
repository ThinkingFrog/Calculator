#include <iostream>
#include "SupportModule.h"
#include "Context.h"

int main() {
    int error_code = 0;
    fs::path plugins_dir("../../plugins");
    Context context(plugins_dir);
    
    error_code = loadPlugins(context);
    if (error_code != 0) {
        std::cout << "Error occured while loading plugins with code " << error_code << std::endl;
        return 1;
    }

    error_code = getExpression(context);
    if (error_code != 0) {
        std::cout << "Error occured while trying to get expression with code " << error_code << std::endl;
        return 1;
    }

    error_code = operateExpression(context);
    if (error_code != 0) {
        std::cout << "Error occured while operataing the expression with code " << error_code << std::endl;
        return 1;
    }

    std::cout << context.result << std::endl;
    return 0;
}