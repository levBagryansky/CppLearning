#include <gtest/gtest.h>

template<typename T>
struct Decay {
private:
    using U = typename std::remove_reference<T>::type;

public:
    using type = std::conditional_t<std::is_array_v<U>,
        std::add_pointer_t<std::remove_extent_t<U>>,  // Q[] -> Q*, where Q[]=U
        std::conditional_t<std::is_function_v<U>,
            std::add_pointer_t<U>,  // R(A) -> * R(A),
            // where R(A)=U
            std::remove_cv_t<U>     // const volatile U -> U
        >>;
};

template <typename T>
using Decay_t = typename Decay<T>::type;

template <typename T, typename U>
constexpr bool Decayed = (std::is_same_v<Decay_t<T>, U> || std::is_same_v<T, Decay_t<U>>);
#define DECAYED(res, to_be_decayed) EXPECT_TRUE((Decayed<res, to_be_decayed>))
#define NOT_DECAYED(res, to_be_decayed) EXPECT_TRUE(!(Decayed<res, to_be_decayed>))

TEST(Decay, Decay) {
    bool b = Decayed<int, int>;
    EXPECT_TRUE(b);
    DECAYED(int, int);
    NOT_DECAYED(int, float);
    DECAYED(int&, int);
    DECAYED(int&&, int);
    DECAYED(const int&, int);
    DECAYED(int[2], int *);
    NOT_DECAYED(int[2][3], int *);
    NOT_DECAYED(int[2][3], int **);
    DECAYED(int[2][3], int (*)[3]);
    DECAYED(int(int), int (*)(int));
}
