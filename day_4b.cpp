#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const static std::vector<std::pair<int, int>> NEIGHBOR_MOVES = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool can_be_removed(int i, int j, const std::vector<std::vector<char>>& grid) {
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

    int removable_rolls = 0;

    while (true) {
        std::vector<std::pair<int, int>> to_remove;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '@' && can_be_removed(i, j, grid)) {
                    to_remove.push_back({i, j});
                }
            }
        }

        if (to_remove.size() == 0) break;

        removable_rolls += to_remove.size();
        for (const auto& [i, j] : to_remove) {
            grid[i][j] = '.';
        }
    }

    std::cout << removable_rolls << '\n';
    return 0;
}
