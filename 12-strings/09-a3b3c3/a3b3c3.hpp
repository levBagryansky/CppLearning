std::string a3b3c3(std::string_view src) {
    std::string result;
    if (src.empty())
        return result;

    char curr = src[0];
    result.push_back(src[0]);
    int counter = 1;
    for (int i = 1; i < src.length(); ++i) {
        if (curr == src[i])
            ++counter;
        else {
            result += std::to_string(counter);
            counter = 1;
            curr = src[i];
            result += curr;
        }
    }
    result += std::to_string(counter);
    return result;
}
