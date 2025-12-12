#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const static std::vector<std::pair<int, int>> NEIGHBOR_MOVES = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool valid(int i, int j, const std::vector<std::vector<char>>& grid) {
    int neighbors = 0;
    for (const auto& [di, dj] : NEIGHBOR_MOVES) {
        int ni = i + di;
        int nj = j + dj;

        if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[0].size() &&
            grid[ni][nj] == '@') {
            neighbors++;
        }
    }

    return neighbors < 4;
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::string line;
    std::vector<std::vector<char>> grid;
    while (getline(input_file, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(std::move(row));
    }

    int valid_rolls = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '@' && valid(i, j, grid)) {
                valid_rolls++;
            }
        }
    }

    std::cout << valid_rolls << '\n';
    return 0;
}
