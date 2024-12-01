#include <cassert>
#include <cmath>
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>

#include <boost/rational.hpp> // support: gmp_rational

#include "RatioException.hpp"

//  ================================================================================================

class Ratio
{
public:

    /* explicit */ Ratio(int num = 0, int den = 1) : m_num(num), m_den(den)
    {
        if (m_den == 0)
        {
            throw RatioException("Ratio::Ratio : invalid denominator\n");
        }

        if (m_den < 0)
        {
            m_num *= -1;
            m_den *= -1;
        }

        reduce();
    }

    explicit operator double() const noexcept
    {
        return 1.0 * m_num / m_den;
    }

private:

    void reduce() noexcept
    {
        auto gcd = std::gcd(m_num, m_den);

        m_num /= gcd;
        m_den /= gcd;
    }

public:

    friend auto & operator>>(std::istream & stream, Ratio & ratio)
    {
        int num; char c; int den;

        stream >> num >> c >> den;

        std::cout << "Hi!" << std::endl;
        if (c != '/')
        {
            throw RatioException("operator>> : invalid input\n");
        }

        ratio = Ratio(num, den);

        return stream;
    }

    friend auto & operator<<(std::ostream & stream, const Ratio & ratio) noexcept
    {
        return stream << ratio.m_num << '/' << ratio.m_den;
    }

//  ------------------------------------------------------------------------------------------------

    auto & operator+=(const Ratio & other) noexcept
    {
        auto lcm = std::lcm(m_den, other.m_den);

        m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);

        m_den = lcm;

        reduce();

        return *this;
    }

    auto & operator-=(const Ratio & other) noexcept
    {
        return *this += other.m_num * -1;
    }

    auto & operator*=(const Ratio & other) noexcept
    {
        m_num *= other.m_num;
        m_den *= other.m_den;

        reduce();

        return *this;
    }

    auto & operator/=(const Ratio & other)
    {
        return *this *= Ratio(other.m_den, other.m_num);
    }

//  -----------------------------------------------------------------------------

    const auto   operator++(int) noexcept { auto copy(*this); *this += 1; return  copy; }
    auto & operator++(   ) noexcept {                   *this += 1; return *this; }
    const auto   operator--(int) noexcept { auto copy(*this); *this -= 1; return  copy; }
    auto & operator--(   ) noexcept {                   *this -= 1; return *this; }

private:

    int m_num = 0;
    int m_den = 1;
};

//  ================================================================================================

auto operator+ (const Ratio & lhs, const Ratio & rhs) noexcept { return Ratio(lhs) += rhs; }
auto operator- (const Ratio & lhs, const Ratio & rhs) noexcept { return Ratio(lhs) -= rhs; }
auto operator* (const Ratio & lhs, const Ratio & rhs) noexcept { return Ratio(lhs) *= rhs; }
auto operator/ (const Ratio & lhs, const Ratio & rhs) { return Ratio(lhs) /= rhs; }

//  ================================================================================================

auto operator< (const Ratio & lhs, const Ratio & rhs) noexcept
{
    return static_cast < double > (lhs) < static_cast < double > (rhs);
}

auto operator> (const Ratio & lhs, const Ratio & rhs) noexcept { return  (rhs < lhs); }
auto operator<=(const Ratio & lhs, const Ratio & rhs) noexcept { return !(lhs > rhs); }
auto operator>=(const Ratio & lhs, const Ratio & rhs) noexcept { return !(lhs < rhs); }
auto operator==(const Ratio & lhs, const Ratio & rhs) noexcept
{
    return !(lhs < rhs) && !(rhs < lhs);
}

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6) noexcept
{
    return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
    [[maybe_unused]] Ratio ratio_1, ratio_2(2), ratio_3 = 3, ratio_4(4, 1);

//	std::vector < int > vector = 1; // error

//  ---------------------------------------------------------------

    assert(equal(std::abs(static_cast < double > (ratio_1)), 0.0));
    assert(equal(std::abs(static_cast < double > (ratio_2)), 2.0));

//  --------------------------------------------------------------------

    while (1) {
        std::cout << "Enter 1 Ratio : ";
        Ratio ratio_5;
        try {
            std::cin >> ratio_5;
            std::cout << "Entered Ratio : " << ratio_5 << '\n';
            break;
        } catch (RatioException exc) {
            std::cerr << "Exception was thrown: " << exc.what() << std::endl;
        }
    }
//  -----------------------------------------------------------

//	assert(ratio_1.operator+=(ratio_2) == Ratio(+2, 1)); // bad

    assert((ratio_1 += ratio_2) == Ratio(+2, 1));
    assert((ratio_1 +=       1) == Ratio(+3, 1));
//	assert((      1 += ratio_2) == Ratio(+3, 1)); // error
//	assert((      1 +=       1) == Ratio(+2, 1)); // error

    assert((ratio_1 -= ratio_2) == Ratio(+1, 1));
    assert((ratio_1 *= ratio_2) == Ratio(+2, 1));
    assert((ratio_1 /= ratio_2) == Ratio(+1, 1));

//  ---------------------------------------------

    assert((ratio_1 ++        ) == Ratio(+1, 1));
    assert((        ++ ratio_2) == Ratio(+3, 1));
    assert((ratio_1 --        ) == Ratio(+2, 1));
    assert((        -- ratio_2) == Ratio(+2, 1));

//	ratio_1++++; // error

//  -----------------------------------------------------------

//	assert(operator+(ratio_1, ratio_2) == Ratio(+3, 1)); // bad

    assert((ratio_1 +  ratio_2) == Ratio(+3, 1));
    assert((ratio_1 +        1) == Ratio(+2, 1));
    assert((      1 +  ratio_2) == Ratio(+3, 1));
    assert((      1 +        1) == Ratio(+2, 1));

    assert((ratio_1 -  ratio_2) == Ratio(-1, 1));
    assert((ratio_1 *  ratio_2) == Ratio(+2, 1));
    assert((ratio_1 /  ratio_2) == Ratio(+1, 2));

//  ---------------------------------------------

    auto f = false, t = true;

//  ----------------------------------

    assert((ratio_1 <  ratio_2) == t);
    assert((ratio_1 >  ratio_2) == f);
    assert((ratio_1 <= ratio_2) == t);
    assert((ratio_1 >= ratio_2) == f);
    assert((ratio_1 == ratio_2) == f);
    assert((ratio_1 != ratio_2) == t);

//  --------------------------------------------

    using rational_t = boost::rational < int > ;

    rational_t rational_1(1, 1);
    rational_t rational_2(2, 1);

//  ---------------------------------------------------------------------------

    assert(equal(std::abs(boost::rational_cast < double > (rational_1)), 1.0));
    assert(equal(std::abs(boost::rational_cast < double > (rational_2)), 2.0));

//  ----------------------------------------------------------------------------------

    std::cout << "Enter 1 rational : "; rational_t rational_3; std::cin >> rational_3;

    std::cout << "Entered rational : " << rational_3 << '\n';


//  ---------------------------------------------------------

    assert((rational_1 += rational_2) == rational_t(+3, 1));
    assert((rational_1 -= rational_2) == rational_t(+1, 1));
    assert((rational_1 *= rational_2) == rational_t(+2, 1));
    assert((rational_1 /= rational_2) == rational_t(+1, 1));

//  --------------------------------------------------------

    assert((rational_1 ++           ) == rational_t(+1, 1));
    assert((           ++ rational_2) == rational_t(+3, 1));
    assert((rational_1 --           ) == rational_t(+2, 1));
    assert((           -- rational_2) == rational_t(+2, 1));

//  --------------------------------------------------------

    assert((rational_1 +  rational_2) == rational_t( 3, 1));
    assert((rational_1 -  rational_2) == rational_t(-1, 1));
    assert((rational_1 *  rational_2) == rational_t( 2, 1));
    assert((rational_1 /  rational_2) == rational_t( 1, 2));

//  --------------------------------------------------------

    assert((rational_1 <  rational_2) == t);
    assert((rational_1 >  rational_2) == f);
    assert((rational_1 <= rational_2) == t);
    assert((rational_1 >= rational_2) == f);
    assert((rational_1 == rational_2) == f);
    assert((rational_1 != rational_2) == t);
}
