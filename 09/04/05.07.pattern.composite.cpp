#include <cassert>
#include <cstddef>
#include <vector>
#include <memory>

//////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

//  -------------------------------------

    virtual std::size_t size() const = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity { public: std::size_t size() const override { return 1; } };

class Server : public Entity { public: std::size_t size() const override { return 2; } };

//////////////////////////////////////////////////////////////////////////////////////////

class Composite : public Entity
{
public:

    ~Composite() {}

//  ------------------------------------

    void add_entity(const std::shared_ptr<Entity>& entity)
    {
        m_entities.push_back(entity);
    }

//  ------------------------------------

    std::size_t size() const override
    {
        auto size = 0uz;

        for (auto entity : m_entities)
        {
            if (entity)
            {
                size += entity->size();
            }
        }

        return size;
    }

private:

    std::vector < std::shared_ptr<Entity> > m_entities;
};


//////////////////////////////////////////////////////////////////////////////////////////

auto make_composite(std::size_t size_1, std::size_t size_2)
{
    auto composite = std::make_shared<Composite>();

    for (auto i = 0uz; i < size_1; ++i) { composite->add_entity(std::make_shared<Client>()); }

    for (auto i = 0uz; i < size_2; ++i) { composite->add_entity(std::make_shared<Server>()); }

    return composite;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto composite = std::make_shared<Composite>();

    for (auto i = 0uz; i < 5; ++i)
    {
        composite->add_entity(make_composite(1, 1));
    }

    auto entity = composite;

    assert(entity->size() == 15);
}
