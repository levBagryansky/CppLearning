#include <gtest/gtest.h>
#include <boost/type_index.hpp>

template<typename T>
struct AddConst {
    using type = const T;
};

template<typename T>
struct AddConst<T &> {
    using type = const T &;
};

template<typename T>
struct AddConst<T &&> {
    using type = const T &&;
};

TEST(AddCont, AddConst) {
    int x = 5;
    AddConst<int>::type addedConst = x;
    int &ref = x;
    const int& cref1 = x;
    AddConst<int &>::type cref2 = x;
    std::add_const<int &>::type cref3 = x;
    std::cout << "AddConst<int>::type == " << boost::typeindex::type_id_with_cvr<decltype(addedConst)>().pretty_name() << std::endl;
    std::cout << "const int& == " << boost::typeindex::type_id_with_cvr<decltype(cref1)>().pretty_name() << std::endl;
    std::cout << "std::add_const<int &> == " << boost::typeindex::type_id_with_cvr<decltype(cref3)>().pretty_name() << std::endl;
    std::cout << "AddConst<int &> == " << boost::typeindex::type_id_with_cvr<decltype(cref2)>().pretty_name() << std::endl;
    volatile int & viref =  x;
    AddConst<volatile int &>::type cviref = viref;
    std::cout << "AddConst<volatile int &> == " << boost::typeindex::type_id_with_cvr<decltype(cviref)>().pretty_name() << std::endl;
    const int cx = 5;
    AddConst<const int>::type ccx = cx;
    std::cout << "AddConst<volatile int &> == " << boost::typeindex::type_id_with_cvr<decltype(cx)>().pretty_name() << std::endl;
}

template<typename T> struct RemoveConst {
    using type = T;
};
template<typename T> struct RemoveConst<const T> {
    using type = T;
};
template<typename T> struct RemoveConst<const T&> {
    using type = T;
};

TEST(RemoveConst, RemoveConst) {
    std::cout << boost::typeindex::type_id_with_cvr<RemoveConst<const int>::type>().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<RemoveConst<const int>::type>().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<RemoveConst<int>::type>().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<RemoveConst<const int&>::type>().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<RemoveConst<const volatile int&>::type>().pretty_name() << std::endl;
}
