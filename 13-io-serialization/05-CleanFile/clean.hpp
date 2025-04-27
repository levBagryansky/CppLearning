#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

bool isWhitespaceOnly(const std::string& line);

void removeEmptyLines(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Failed to open file for reading: " << filename << "\n";
        return;
    }

    std::vector<std::string> nonEmptyLines;
    std::string line;

    while (std::getline(inputFile, line)) {
        if (!line.empty() && !isWhitespaceOnly(line)) {
            nonEmptyLines.push_back(line);
        }
    }

    inputFile.close();

    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    for (const auto& l : nonEmptyLines) {
        outputFile << l << '\n';
    }

    std::cout << "File successfully cleaned of empty and whitespace-only lines.\n";
}

bool isWhitespaceOnly(const std::string& line) {
    return std::all_of(line.begin(), line.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    });
}