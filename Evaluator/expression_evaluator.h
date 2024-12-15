#include <cctype>
#include <stdexcept>
#include <sstream>
#include <algorithm>
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
// 判断字符是否为数字或小数点
bool ExpressionEvaluator::isNumberOrDot(char c) {
    return std::isdigit(c) || c == '.';
}

// 判断字符是否为运算符
bool ExpressionEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 获取运算符的优先级
int ExpressionEvaluator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == 'u') return 3; // 'u' 表示一元负号
    return 0;
}

// 执行基本运算，包括一元运算符
double ExpressionEvaluator::applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division By Zero!");
            return a / b;
        case 'u': return -a; // 一元负号
    }
    throw std::runtime_error("Unknown Operator!");
}

// 判断字符是否为一元负号
bool ExpressionEvaluator::isUnaryMinus(const std::string &expr, size_t pos) {
    // 一元负号可能出现在以下位置：
    // 1. 表达式开头
    // 2. 左括号后面
    // 3. 运算符后面
    return pos == 0 || expr[pos - 1] == '(' || isOperator(expr[pos - 1]);
}

// 解析数字，支持科学计数法和一元负号
double ExpressionEvaluator::parseNumber(const std::string &expr, size_t &pos) {
    size_t start = pos;
    bool hasDecimal = false;
    bool hasExponent = false;
    bool isNegative = false;

    // 处理一元负号
    if (expr[pos] == '-' && isUnaryMinus(expr, pos)) {
        isNegative = true;
        pos++; // 跳过负号
        start = pos; // 更新起始位置
    }

    while (pos < expr.length() &&
           (isNumberOrDot(expr[pos]) || expr[pos] == 'e' || expr[pos] == 'E' ||
            ( (expr[pos] == '-' || expr[pos] == '+') && (expr[pos - 1] == 'e' || expr[pos - 1] == 'E')) )) {
        if (expr[pos] == '.') {
            if (hasDecimal) break; // 只允许一个小数点
            hasDecimal = true;
        } else if (expr[pos] == 'e' || expr[pos] == 'E') {
            if (hasExponent) break; // 只允许一个指数符号
            hasExponent = true;
        }
        pos++;
    }

    std::istringstream iss(expr.substr(start, pos - start));
    double value;
    iss >> value;
    if (iss.fail()) {
        throw std::runtime_error("Invalid number format");
    }

    // 如果之前有负号，返回负数
    if (isNegative) {
        value = -value;
    }

    return value;
}

// 移除字符串中的所有空格
std::string ExpressionEvaluator::removeSpaces(const std::string &expr) {
    std::string result = expr;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

// 检查表达式是否合法
bool ExpressionEvaluator::isValidExpression(const std::string &expr) {
    std::string noSpaceExpr = removeSpaces(expr); // 移除所有空格

    if (noSpaceExpr.empty()) return false;

    std::stack<char> bracketStack;
    bool hasNumber = false;
    bool lastWasOperator = false;

    for (size_t i = 0; i < noSpaceExpr.length(); ++i) {
        char c = noSpaceExpr[i];

        if (c == '(') {
            bracketStack.push(c);
            lastWasOperator = true; // '(' 后面应该是数字或一元运算符
            hasNumber = false;
        } else if (c == ')') {
            if (bracketStack.empty()) {
                // 右括号没有匹配的左括号
                return false;
            }
            bracketStack.pop();
            lastWasOperator = false;
            hasNumber = true; // 右括号后面应该有数字
        } else if (isNumberOrDot(c) || c == 'e' || c == 'E') {
            if ((c == 'e' || c == 'E') && !hasNumber) {
                // 'e' 前必须有数字
                return false;
            }
            if (c == '.' && (i == 0 || !std::isdigit(noSpaceExpr[i - 1]))) return false;
            hasNumber = true;
            lastWasOperator = false;
        } else if (c == '-' && isUnaryMinus(noSpaceExpr, i)) {
            // 允许一元负号
            if (!lastWasOperator && i != 0) {
                // 一元运算符必须跟在另一个运算符或左括号之后
                return false;
            }
            lastWasOperator = true;
            hasNumber = false;
        } else if (c == '+' && isUnaryMinus(noSpaceExpr, i)) {
            // 不允许一元正号，直接返回非法
            return false;
        } else if (isOperator(c)) {
            if (lastWasOperator) return false; // 运算符连续使用
            if (!hasNumber && !(c == '-' )) return false; // 运算符前必须有数字
            lastWasOperator = true;
            hasNumber = false;
        } else {
            // 非法字符
            return false;
        }
    }

    return bracketStack.empty() && hasNumber && !lastWasOperator;
}

// 计算表达式的值
double ExpressionEvaluator::evaluate(const std::string &expr) {
    std::string noSpaceExpr = removeSpaces(expr); // 移除所有空格

    if (!isValidExpression(noSpaceExpr)) throw std::runtime_error("Invalid Expression!");

    std::stack<double> values;
    std::stack<char> ops;

    size_t i = 0;
    while (i < noSpaceExpr.length()) {
        char c = noSpaceExpr[i];

        if (isNumberOrDot(c) || c == 'e' || c == 'E' ||
            (c == '-' && isUnaryMinus(noSpaceExpr, i))) {
            if ((c == '-' ) && isUnaryMinus(noSpaceExpr, i)) {
                // 处理一元运算符
                char unaryOp = 'u'; // 'u' for unary minus
                while (!ops.empty() && ops.top() != '(' && precedence(ops.top()) >= precedence(unaryOp)) {
                    char op = ops.top(); ops.pop();
                    if (op == 'u') {
                        if (values.empty()) throw std::runtime_error("Invalid Expression!");
                        double val = values.top(); values.pop();
                        values.push(applyOp(val, 0, 'u'));
                    } else {
                        if (values.size() < 2) throw std::runtime_error("Invalid Expression!");
                        double val2 = values.top(); values.pop();
                        double val1 = values.top(); values.pop();
                        values.push(applyOp(val1, val2, op));
                    }
                }
                ops.push(unaryOp);
                i++;
            } else {
                double val = parseNumber(noSpaceExpr, i);
                values.push(val);
            }
        } else if (c == '(') {
            ops.push(c);
            i++;
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top(); ops.pop();
                if (op == 'u') {
                    if (values.empty()) throw std::runtime_error("Invalid Expression!");
                    double val = values.top(); values.pop();
                    values.push(applyOp(val, 0, 'u'));
                } else {
                    if (values.size() < 2) throw std::runtime_error("Invalid Expression!");
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, op));
                }
            }

            if (ops.empty()) throw std::runtime_error("Mismatched parentheses!");
            ops.pop(); // 移除 '('
            i++;
        } else if (isOperator(c)) {
            while (!ops.empty() && ops.top() != '(' && precedence(ops.top()) >= precedence(c)) {
                char op = ops.top(); ops.pop();
                if (op == 'u') {
                    if (values.empty()) throw std::runtime_error("Invalid Expression!");
                    double val = values.top(); values.pop();
                    values.push(applyOp(val, 0, 'u'));
                } else {
                    if (values.size() < 2) throw std::runtime_error("Invalid Expression!");
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, op));
                }
            }

            ops.push(c);
            i++;
        } else {
            // 非法字符
            throw std::runtime_error("Invalid character encountered!");
        }
    }

    while (!ops.empty()) {
        char op = ops.top(); ops.pop();
        if (op == '(' || op == ')') throw std::runtime_error("Mismatched parentheses!");

        if (op == 'u') {
            if (values.empty()) throw std::runtime_error("Invalid Expression!");
            double val = values.top(); values.pop();
            values.push(applyOp(val, 0, 'u'));
        } else {
            if (values.size() < 2) throw std::runtime_error("Invalid Expression!");
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            values.push(applyOp(val1, val2, op));
        }
    }

    if (values.size() != 1) throw std::runtime_error("Invalid Expression!");

    return values.top();
}
