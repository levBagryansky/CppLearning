#pragma once

#include <cassert>
#include <iostream>
#include <string>

namespace entity {

using namespace std::literals;

class Entity
{
public:

    Entity();

//	Entity() : m_data_1(s_data_1), m_data_3(0), m_data_2(0) {} // error

//  -------------------------------------------------------------------

    Entity(const int & data_1, int data_2, int data_3);

    Entity(const int & data_1, int data_2);

//  ---------------------------------------------------------------------

    ~Entity();

//  ----------------------------------------

    auto data_1() const { return m_data_1; }
    auto data_2() const { return m_data_2; }
    auto data_3() const { return m_data_3; }

//  ----------------------------------------

    const auto & data_as_string() const {
        //	m_data_3 = 0; // error

        if (m_cached_data.is_invalid)
        {
            m_cached_data.update(*this);
        }

        return m_cached_data.string;
    }


//  -----------------------------------------------------

//	void set_data_3(int data) { m_data_3 = data; } // bad

    void set_data_3(int data);

//  ------------------------------------

    static void test();

private:

    struct Cached_Data
    {
        void update(const Entity & entity);

        std::string string; bool is_invalid = true;
    };

//  -----------------------------------------------

    static inline       auto s_data_1 = 0;

    static        const auto s_data_2 = 0;

//	static        const auto s_data_3 = "aaaaa"s; // error

    static inline const auto s_data_4 = "aaaaa"s;

//  ---------------------------------------------

    const int & m_data_1 = 0;

    const int   m_data_2 = 0;

    int   m_data_3 = 0;

//  ----------------------------------

     mutable Cached_Data m_cached_data;
};

} // entity

