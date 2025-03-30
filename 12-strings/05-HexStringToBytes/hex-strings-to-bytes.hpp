namespace detail {

uint8_t HexCharToNum(char c) {
    assert((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
    return (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10;
}

uint8_t pairToByte(char c1, char c2) {
    return 16 * HexCharToNum(c1) + HexCharToNum(c2);
}

}

template <typename Vector = std::vector<uint8_t>>
Vector hexStringToVec(std::string_view str) {
    assert(str.size() % 2 == 0);
    Vector vec{};
    vec.reserve(str.size() / 2);
    for (int i = 0; i < str.size(); i += 2) {
        vec.push_back(
            detail::pairToByte(str[i], str[i+1])
        );
    }
    return vec;
}
