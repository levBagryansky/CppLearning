#include <iostream>
#include <vector>
#include <iomanip>

std::vector<int> getNextRow(const std::vector<int>& prev) {
    std::vector<int> row;
    row.push_back(1);
    for (size_t i = 1; i < prev.size(); ++i) {
        row.push_back(prev[i - 1] + prev[i]);
    }
    row.push_back(1);
    return row;
}

void printPascalsTriangle(int numRows) {
    std::vector<std::vector<int>> triangle;
    triangle.push_back({1});

    for (int i = 1; i < numRows; ++i) {
        triangle.push_back(getNextRow(triangle.back()));
    }

    int maxValue = *std::max_element(triangle.back().begin(), triangle.back().end());
    int cellWidth = std::to_string(maxValue).length() + 2;  // "126" → 3 + 2 = 5

    for (const auto& row : triangle) {
        int totalWidth = numRows * cellWidth;
        int rowWidth = static_cast<int>(row.size()) * cellWidth;
        int padding = (totalWidth - rowWidth) / 2;
        std::cout << std::string(padding, ' ');

        for (int value : row) {
            std::cout << std::setw(cellWidth) << value;
        }
        std::cout << "\n";
    }
}

int main() {
    printPascalsTriangle(10);
    return 0;
}