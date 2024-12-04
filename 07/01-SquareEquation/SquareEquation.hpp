#pragma once

#include <valarray>

/*
 *     Реализуйте алгоритм решения квадратного уравнения, принимающий в качестве аргументов коэффициенты
 * уравнения a, b и c. Гарантируется, что коэффициент a не равен нулю. Квадратное уравнение может иметь 2, 1
 * или 0 решений. Для хранения решений используйте класс-хранилище std::variant, в котором для представления
 * 0 решений будет использоваться тип std::monostate. Для представления двух решений рекомендуется
 * использовать тип std::pair, а для представления одного решения достаточно одиночного double. Точность
 * сравнения чисел с плавающей точкой в данной задаче можно не затрагивать, в случае с дискриминантом
 * допускается проверка условия d == 0.0. Также не используйте функцию std::visit из публичных решений.
 */

class SquareEquation {
public:
    using answer_t = std::variant<std::monostate, double, std::pair<double, double>>;
    SquareEquation(double a, double b, double c): a_(a), b_(b), c_(c), answer_(std::nullopt) {
        assert(a_ != 0.0);
    }
    answer_t answer() {
        if (!answer_.has_value())
            compute_ans();
        return answer_.value();
    }

private:
    void compute_ans() {
        double disc = std::sqrt(b_ * b_ - 4 * a_ * c_);
        if (disc > 0.0) {
            answer_.emplace(
                std::pair<double, double> (
                    (-b_ - disc) / 2 * a_,
                    (-b_ + disc) / 2 * a_
                )
            );
        } else if (disc == 0.0) {
            answer_.emplace(-b_ / 2 * a_);
        } else { // disc < 0.0
            answer_.emplace(std::monostate{});
        }
    }

public:
    const double a_, b_, c_;
private:
    std::optional<answer_t> answer_;
};
