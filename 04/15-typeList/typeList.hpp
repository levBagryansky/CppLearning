#include <iostream>
#include <typeinfo>
#include <type_traits>

#include <boost/type_index.hpp>

//  ================================================================================================

template < typename ... Ts > struct List {};

//  ================================================================================================

template < typename     L  > struct Size {};

template < typename ... Ts > struct Size < List < Ts ... > >
{
    static constexpr auto value = sizeof...(Ts);
};

template < typename L > inline constexpr auto  size_v = Size < L > ::value;

template < typename L > inline constexpr auto empty_v = (size_v < L > == 0);

//  ================================================================================================

template <             typename     L  > struct Front {};

template < typename T, typename ... Ts > struct Front < List < T, Ts ... > > { using type = T; };

template < typename L > using front = typename Front < L > ::type;

//  ================================================================================================

template < typename T, typename     L  > struct Push_Front {};

template < typename T, typename ... Ts > struct Push_Front < T, List < Ts ... > >
{
    using type = List < T, Ts ... > ;
};

template < typename T, typename L > using push_front = typename Push_Front < T, L > ::type;

//  ================================================================================================

template <             typename     L  > struct Pop_Front {};

template < typename T, typename ... Ts > struct Pop_Front < List < T, Ts ... > >
{
    using type = List < Ts ... > ;
};

template < typename L > using pop_front = typename Pop_Front < L > ::type;

//  ================================================================================================

template <             typename     L  > struct Back {};

template < typename T                  > struct Back < List < T > > { using type = T; };

template < typename T, typename ... Ts > struct Back < List < T, Ts ... > >
{
    using type = typename Back < List < Ts ... > > ::type;
};

template < typename L > using back = typename Back < L > ::type;

//  ================================================================================================

template < typename T, typename L, bool E = empty_v < L > > struct Push_Back {};

template < typename T, typename L > struct Push_Back < T, L, false >
{
    using type = push_front < front < L > , typename Push_Back < T, pop_front < L > > ::type > ;
};

template < typename T, typename L > struct Push_Back < T, L, true >
{
    using type = push_front < T, L > ;
};

template < typename T, typename L > using push_back = typename Push_Back < T, L > ::type;

//  ================================================================================================

template <             typename     L  > struct Pop_Back{};

template < typename T                  > struct Pop_Back < List < T > > { using type = List <> ; };

template < typename T, typename ... Ts > struct Pop_Back < List < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < List < Ts ... > > ::type > ;
};

template < typename L > using pop_back = typename Pop_Back < L > ::type;

//  ================================================================================================

template < typename L, auto N > struct Nth : public Nth < pop_front < L > , N - 1 > {};

template < typename L > struct Nth < L, 0 > : public Front < L > {};

template < typename L, auto N > using nth = typename Nth < L, N > ::type;

//  ================================================================================================

template<typename T, typename U>
struct Or: std::conditional<std::is_same_v<T, std::true_type>, std::true_type, U> {};

template<typename T, typename L>
struct Contains: std::integral_constant<
    bool,
    std::is_same<T, back<L>>::value || Contains<T, pop_back<L>>::value
    > {};

template<typename T, typename U>
struct Contains<T, List<U>>: std::is_same<T, U> {};

template<typename T>
struct Contains<T, List<>>: std::false_type {};

template<typename T, typename L>
constexpr bool contains = Contains<T, L>::value;

//  ================================================================================================

template < typename L, bool E = empty_v < L > > struct Max_Type {};

template < typename L > struct Max_Type < L, true  > { using type = char; };

template < typename L > struct Max_Type < L, false >
{
private:

    using contender = front < L > ;

    using best = typename Max_Type < pop_front < L > > ::type;

public:

    using type = std::conditional_t < (sizeof(contender) >= sizeof(best)), contender, best > ;

}; // template < typename L > struct Max_Type < L, false >

template < typename L > using max_type = typename Max_Type < L > ::type;

//  ================================================================================================

int main_()
{
    using list_0 = List <            > ;
    using list_1 = List < bool       > ;
    using list_2 = List < bool, char > ;

    using list_3 = push_back < int, list_2 > ;

//  ================================================================================================

    static_assert(size_v < list_0 > == 0 &&  empty_v < list_0 > );
    static_assert(size_v < list_1 > == 1 && !empty_v < list_1 > );
    static_assert(size_v < list_2 > == 2 && !empty_v < list_2 > );
    static_assert(size_v < list_3 > == 3 && !empty_v < list_3 > );

//  ================================================================================================

//  using     front_t_0 =     front < list_0 > ; // error
//  using pop_front_t_0 = pop_front < list_0 > ; // error

//  using      back_t_0 =      back < list_0 > ; // error
//  using  pop_back_t_0 =  pop_back < list_0 > ; // error

//  ================================================================================================

    std::cout << boost::typeindex::type_id_with_cvr < list_0 > ().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr < list_1 > ().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr < list_2 > ().pretty_name() << std::endl;

//  ================================================================================================

    static_assert(std::is_same_v < front < push_front < int, list_2 > > , int  > );
    static_assert(std::is_same_v < front <  pop_front <      list_2 > > , char > );

    static_assert(std::is_same_v <  back <  push_back < int, list_2 > > , int  > );
    static_assert(std::is_same_v <  back <   pop_back <      list_2 > > , bool > );

//  ================================================================================================

    static_assert(std::is_same_v < nth < list_3, 0 > , bool > );
    static_assert(std::is_same_v < nth < list_3, 1 > , char > );
    static_assert(std::is_same_v < nth < list_3, 2 > , int  > );

//  ================================================================================================

    static_assert(std::is_same_v < max_type < list_3 > , int > );

    return 0;
}
