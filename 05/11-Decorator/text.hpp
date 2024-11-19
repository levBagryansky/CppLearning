#pragma once

#include <algorithm>
#include <utility>

class Text {
public:
    virtual std::string content() const = 0;
    virtual ~Text() = default;
};

class CapitalizedText : public Text {
public:
    explicit CapitalizedText(std::unique_ptr<Text> text) : origin_(std::move(text)) {}

    std::string content() const override {
        std::string text = origin_->content();
        std::ranges::transform(text, text.begin(), [](unsigned char c) { return std::toupper(c); });
        return text;
    }

private:
    std::unique_ptr<Text> origin_;
};

class TrimmedText : public Text {
public:
    explicit TrimmedText(std::unique_ptr<Text> text) : origin_(std::move(text)) {}

    std::string content() const override {
        std::string content = origin_->content();
        auto start = std::find_if_not(content.begin(), content.end(),
                                      [](unsigned char ch) { return std::isspace(ch); });
        auto end = std::find_if_not(content.rbegin(), content.rend(), [](unsigned char ch) {
            return std::isspace(ch);
        }).base();
        return (start < end) ? std::string(start, end) : std::string();
    }

private:
    std::unique_ptr<Text> origin_;
};

class TextFromString : public Text {
public:
    explicit TextFromString(std::string content) : content_(std::move(content)) {}

    std::string content() const override { return content_; }

private:
    std::string content_;
};



