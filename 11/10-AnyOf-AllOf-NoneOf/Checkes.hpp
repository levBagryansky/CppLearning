#pragma once

#include <ranges>

template <typename C, typename T>
concept RangeOf = std::ranges::range<C> &&
                  std::same_as<T, std::ranges::range_value_t<C>>;

template <typename T, RangeOf<T> C>
bool has_one(const C& container, const T& item) {
    return std::ranges::find(container, item) != std::ranges::end(container);
}

template <typename C, typename T, typename... Ts>
concept SameElementType =
    RangeOf<C, T> &&
    (std::same_as<Ts, std::ranges::range_value_t<C>> && ...);

template <typename Container, typename T, typename... Ts>
requires SameElementType<Container, T, Ts ...>
bool any_of(const Container& container, const T& first, const Ts&... rest) {
    return has_one(container, first) || (... || has_one(container, rest));
}

template <typename Container, typename T, typename... Ts>
requires SameElementType<Container, T, Ts ...>
bool all_of(const Container& container, const T& first, const Ts&... rest) {
    return has_one(container, first) && (... && has_one(container, rest));
}

template <typename Container, typename T, typename... Ts>
requires SameElementType<Container, T, Ts ...>
bool none_of(const Container& container, const T& first, const Ts&... rest) {
    return !any_of(container, first, rest ...);
}
