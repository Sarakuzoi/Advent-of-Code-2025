#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

int splits = 0;

int count_splits(const std::vector<std::string>& grid, int level,
                 std::unordered_set<int> beams) {
    if (level > grid.size()) return 0;

    const int WIDTH = grid[level].size();
    int splits = 0;

    for (int i = 0; i < WIDTH; i++) {
        if (grid[level][i] == '^' && beams.find(i) != beams.end()) {
            splits += 1;
            beams.erase(i);
            if (i < WIDTH - 1) beams.insert(i + 1);
            if (i > 0) beams.insert(i - 1);
        }
    }

    return splits + count_splits(grid, level + 1, beams);
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::string line;
    std::vector<std::string> grid;
    while (getline(input_file, line)) {
        grid.push_back(line);
    }

    auto start_pos = std::strchr(grid[0].c_str(), 'S') - grid[0].c_str();
    std::cout << count_splits(grid, 1, {static_cast<int>(start_pos)}) << '\n';
    return 0;
}