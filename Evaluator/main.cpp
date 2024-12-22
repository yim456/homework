#include <iostream>
#include "expression_evaluator.h"
#include <sstream>

void runTests() {
    const std::pair<std::string, std::string> tests[] = {
        {"3 + 4 * 2 / ( 1 - 5 )", "1"},
        {"3 + 4 * 2 / ( 1 - 5", "ILLEGAL"},
        {"3 + * 4", "ILLEGAL"},
        {"+ 3 + 4", "ILLEGAL"},
        {"3 + 4 +", "ILLEGAL"},
        {"3 / 0", "ILLEGAL"},
        {"3 + 4 @ 2", "ILLEGAL"},
        {"3.5 + 2.5 * 4.0", "13.5"},
        {"( ( 3 + 4 ) * ( 2 - 1 ) )", "7"},
        {"", "ILLEGAL"},
        {"42", "42"},
        {"1 + -2.1", "-1.1"},
        {"-1 + 2e2", "199"},
        {"1 + -2.1e-1", "0.79"},
        {"1.23e-2 + 4.56e3", "4560.0123"},
        {"1e+2 + 2", "102"},
        {"-1e+2 + 2", "-98"},
        {"1e++2", "ILLEGAL"},
        {"1e2e3", "ILLEGAL"},
        {"1.2.3 + 4", "ILLEGAL"},
        {"((1 + 2) * (3 + (4 - 5)))", "6"},
        {"-3 + +4", "ILLEGAL"},
        {"-3 + -4", "-7"},
        {"3 + 4 * -2 / (1 - 5)^2", "ILLEGAL"}, // 不支持幂运算
        {"2e+3 + 1", "2001"},
        {"2e-3 + 1", "1.002"},
        {"2e", "ILLEGAL"},
        {"2e+", "ILLEGAL"},
        {"(1 + 2))", "ILLEGAL"},
        {"((1 + 2)", "ILLEGAL"},
        {"-(5+6)", "-11"}, // 新增测试用例
        {"1++2.1", "ILLEGAL"}, // 新增测试用例
    };

    std::cout << "Running Test Cases:\n";
    for (const auto &test : tests) {
        try {
            double result = ExpressionEvaluator::evaluate(test.first);
            // 格式化结果以匹配预期输出的小数位数
            std::ostringstream oss;
            oss << result;
            std::string resultStr = oss.str();
            std::cout << "Test: \"" << test.first << "\" -> Result: " << resultStr << " (Expected: " << test.second << ")\n";
        } catch (const std::runtime_error& e) {
            std::cout << "Test: \"" << test.first << "\" -> ILLEGAL (Expected: " << test.second << ")\n";
        }
    }
}

int main() {
    runTests();

    // 交互模式
    std::string expression;
    std::cout << "\nEnter an arithmetic expression (or type 'exit' to quit): ";
    while (std::getline(std::cin, expression) && expression != "exit") {
        try {
            double result = ExpressionEvaluator::evaluate(expression);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "ILLEGAL" << std::endl;
        }
        std::cout << "Enter an arithmetic expression (or type 'exit' to quit): ";
    }

    return 0;
}
