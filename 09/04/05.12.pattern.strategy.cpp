#include <iostream>
#include <memory>
#include <cassert>

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Strategy
{
public:

    virtual ~Strategy() = default;

//  ------------------------------

    virtual void test() const = 0;
};

////////////////////////////////////////////

class Slow : public Strategy
{
public:

    void test() const override
    {
        std::cout << "Slow::test\n";
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Fast : public Strategy
{
public:

    void test() const override
    {
        std::cout << "Fast::test\n";
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    Entity(std::unique_ptr<Strategy> strategy) : m_strategy(std::move(strategy)) {
        assert(m_strategy);
    }

//  --------------------------------------------------------------

    void test() const
    {
        m_strategy->test();
    }

private:

    std::unique_ptr<Strategy> m_strategy;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto strategy = std::make_unique<Slow>();

    Entity entity(std::move(strategy));

    entity.test();
}
