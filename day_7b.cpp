#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct PairHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};

using Cache = std::unordered_map<std::pair<int, int>, long long, PairHash>;

long long count_timelines(const std::vector<std::string>& grid, int row,
                          int col, Cache& cache) {
    if (row >= static_cast<int>(grid.size())) return 1;
    if (col < 0 || col >= static_cast<int>(grid[row].size())) return 0;

    if (auto it = cache.find({row, col}); it != cache.end()) {
        return it->second;
    }

    long long result = 0;
    if (grid[row][col] == '^') {
        result = count_timelines(grid, row + 1, col - 1, cache) +
                 count_timelines(grid, row + 1, col + 1, cache);
    } else {
        result = count_timelines(grid, row + 1, col, cache);
    }

    return cache[{row, col}] = result;
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Error: Could not open input.in\n";
        return 1;
    }

    std::vector<std::string> grid;
    for (std::string line; std::getline(input_file, line);) {
        if (!line.empty()) grid.push_back(line);
    }

    if (grid.empty()) return 0;

    size_t start_col = grid[0].find('S');
    Cache cache;
    std::cout << count_timelines(grid, 1, static_cast<int>(start_col), cache)
              << std::endl;

    return 0;
}