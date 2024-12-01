#include <utility>

#pragma once

class RatioException : public std::exception {
public:

    explicit RatioException(std::string what) : what_(std::move(what)) {}

//  ------------------------------------------------------------------------------------------------

    const char * what() const noexcept override
    {
        return what_.c_str();
    }

private:

    std::string what_;
};
