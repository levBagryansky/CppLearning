#include <gtest/gtest.h>

#include "clean.hpp"

void writeLinesToFile(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    for (const auto& line : lines) {
        file << line << "\n";
    }
}

std::vector<std::string> readLinesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

class RemoveEmptyLinesTest : public ::testing::Test {
protected:
    std::string testFilename = "temp_test_file.txt";

    void TearDown() override {
        std::remove(testFilename.c_str());
    }
};

TEST_F(RemoveEmptyLinesTest, RemovesEmptyAndWhitespaceLines) {
    std::vector<std::string> input = {
        "First line",
        "   ",
        "",
        "\t",
        "Second line",
        "",
        "  Third line   "
    };

    std::vector<std::string> expected = {
        "First line",
        "Second line",
        "  Third line   "
    };

    writeLinesToFile(testFilename, input);
    removeEmptyLines(testFilename);
    auto result = readLinesFromFile(testFilename);

    EXPECT_EQ(result, expected);
}

TEST_F(RemoveEmptyLinesTest, KeepsAllNonEmptyLines) {
    std::vector<std::string> input = {
        "A",
        "B",
        "C"
    };

    writeLinesToFile(testFilename, input);
    removeEmptyLines(testFilename);
    auto result = readLinesFromFile(testFilename);

    EXPECT_EQ(result, input);
}

TEST_F(RemoveEmptyLinesTest, AllLinesRemoved) {
    std::vector<std::string> input = {
        "   ",
        "\t\t",
        "",
        "      "
    };

    writeLinesToFile(testFilename, input);
    removeEmptyLines(testFilename);
    auto result = readLinesFromFile(testFilename);

    EXPECT_TRUE(result.empty());
}

TEST_F(RemoveEmptyLinesTest, HandlesEmptyFile) {
    std::ofstream file(testFilename);
    file.close();

    removeEmptyLines(testFilename);
    auto result = readLinesFromFile(testFilename);

    EXPECT_TRUE(result.empty());
}
