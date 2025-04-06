#include <utility>
#include <regex>

class URL {
public:
    URL(std::string protocol, std::string hostname, std::string port, std::string path):
        protocol_(std::move(protocol)), hostname_(std::move(hostname)), port_(std::move(port)), path_(std::move(path)){}

    explicit URL(const std::string &src) {
        auto reg = R"(^(https?)://([^:/\s]+)(?::(\d+))?(/[^?\s]*)?)";
        std::regex url_regex(R"(^(https?)://([^:/\s]+)(?::(\d+))?(/[^?\s]*)?)");

        std::smatch match;
        if (std::regex_match(src, match, url_regex)) {
            protocol_ = match[1];
            hostname_ = match[2];
            port_ = match[3];
            path_ = match[4];
        } else {
            std::cout << "Incorrect URL\n";
        }

    }

    friend bool operator==(const URL& lhs, const URL& rhs);
private:
    std::string protocol_, hostname_, port_, path_;
};

bool operator==(const URL& lhs, const URL& rhs) {
    return lhs.protocol_ == rhs.protocol_ &&
        lhs.hostname_ == rhs.hostname_ &&
        lhs.port_ == rhs.port_ &&
        lhs.path_ == rhs.path_;
}
