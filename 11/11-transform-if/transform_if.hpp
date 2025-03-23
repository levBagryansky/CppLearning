template<typename InIt, typename OutIt, typename Predicate,
    typename Operation>
OutIt transform_if(InIt first, InIt last,
                OutIt result, Predicate pred, Operation op)
{
    for (; first != last; ++first) {
        if (pred(*first)) {
            *result = op(*first);
            ++result;
        }
    }
    return result;
}

