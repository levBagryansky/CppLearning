#pragma once

#include <stack>

class RPN_stack {
public:
    void push(const std::string& token) {
        assert(!token.empty());
        if (isdigit(token[0]))
            stack_.push(std::stod(token));
        else {
            assert(token.size() == 1);
            double opr2 = stack_.top();
            stack_.pop();
            double opr1 = stack_.top();
            stack_.pop();

            switch (token[0]) {
                case '-':
                    stack_.push(opr1 - opr2);
                    break;
                case '+':
                    stack_.push(opr1 + opr2);
                    break;
                case '*':
                    stack_.push(opr1 * opr2);
                    break;
                case '/':
                    if (is_zero(opr2))
                        throw std::runtime_error("Division by 0 is prohibited");
                    stack_.push(opr1 / opr2);
                    break;
                default:
                    throw std::runtime_error("Illegal operation");
            }
        }
    }
    double top() {
        return stack_.top();
    }
private:
    std::stack<double> stack_{};

    static bool is_zero(double opr) {
        return std::abs(opr) < std::numeric_limits<double>::epsilon();
    }
};

double calculate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string word;
    RPN_stack stack;
    while (iss >> word) {
        stack.push(word);
    }
    std::cout << stack.top() << std::endl;
    return stack.top();
}
