#include "gtest/gtest.h"

#include <algorithm>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> emails(const std::string& str) {
    const std::regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{1,}\b)");
    std::vector<std::string> emails;
    std::ranges::for_each(std::sregex_iterator(std::cbegin(str), std::cend(str), pattern),
                          std::sregex_iterator(),
                          [&emails](const auto& matches) { emails.push_back(matches[0]); });
    return emails;
}


TEST(EmailExtractionTest, EmptyInput) { EXPECT_EQ(emails(""), std::vector<std::string>({})); }

TEST(EmailExtractionTest, NoEmailsInText) {
const std::string text = R"(
        This is just regular text without any emails.
        Some symbols: @hello, test@, @test.com
        Numbers: 12345, random!text
    )";
EXPECT_EQ(emails(text), std::vector<std::string>({}));
}

TEST(EmailExtractionTest, ValidEmails) {
const std::string text = R"(
        Contact us at: john.doe@example.com or support@company.org.
        Student emails: student_2023@university.edu, a.b@c.d.xyz
        Special cases: email+filter@gmail.com, name@sub.domain.co.uk
    )";
EXPECT_EQ(emails(text),
    std::vector<std::string>({"john.doe@example.com", "support@company.org",
                              "student_2023@university.edu", "a.b@c.d.xyz",
                              "email+filter@gmail.com", "name@sub.domain.co.uk"}));
}

TEST(EmailExtractionTest, InvalidEmails) {
const std::string text = R"(
        Invalid formats:
        plaintext
        @missing.start
        missing@at
        double@@sign.com
        invalid@chars_here.com
        missing@tld.
    )";
EXPECT_EQ(emails(text), std::vector<std::string>({}));
}

TEST(EmailExtractionTest, MixedContent) {
const std::string text = R"(
        Valid: contact@valid.com, another@good.org
        Invalid: bad@email, @wrong.com
        Almost valid: almost@valid. but with space
        Trash: !@#$%^&*
        Valid but tricky: "spaces@around.com" (should extract without quotes)
    )";
EXPECT_EQ(emails(text), std::vector<std::string>(
    {"contact@valid.com", "another@good.org", "spaces@around.com"}));
}

TEST(EmailExtractionTest, EdgeCases) {
const std::string text = R"(
        Minimal: a@b.c
        Long domain: email@sub.sub2.sub3.example.com
        Special chars: user+filter@domain.com
        Numbers: 1234@numbers.com
        Hyphens: hyphen-ated@domain-name.com
        Quotes: "email@inside.quotes"
    )";
EXPECT_EQ(emails(text),
    std::vector<std::string>({"a@b.c", "email@sub.sub2.sub3.example.com",
                              "user+filter@domain.com", "1234@numbers.com",
                              "hyphen-ated@domain-name.com", "email@inside.quotes"}));
}
