#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <stack>

class ExpressionEvaluator {
public:
    // 检查表达式是否合法
    static bool isValidExpression(const std::string &expr);

    // 计算表达式的值
    static double evaluate(const std::string &expr);

private:
    // 解析数字，支持科学计数法
    static double parseNumber(const std::string &expr, size_t &pos);

    // 获取运算符的优先级
    static int precedence(char op);

    // 执行基本运算，包括一元运算符
    static double applyOp(double a, double b, char op);

    // 判断字符是否为数字或小数点
    static bool isNumberOrDot(char c);

    // 判断字符是否为运算符
    static bool isOperator(char c);

    // 判断字符是否为一元负号
    static bool isUnaryMinus(const std::string &expr, size_t pos);

    // 移除字符串中的所有空格
    static std::string removeSpaces(const std::string &expr);
};

#endif // EXPRESSION_EVALUATOR_H
