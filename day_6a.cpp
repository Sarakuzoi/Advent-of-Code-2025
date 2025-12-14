#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

long long solve_problem(int i, char op,
                        const std::vector<std::vector<int>>& grid) {
    long long res = op == '*' ? 1 : 0;
    for (int j = 0; j < grid.size(); j++) {
        res = op == '*' ? (res * grid[j][i]) : (res + grid[j][i]);
    }

    return res;
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::vector<std::vector<int>> grid;
    std::vector<char> ops;
    std::string line;
    while (getline(input_file, line)) {
        std::stringstream ss(line);
        std::vector<int> num_line;
        int num;

        if (ss.peek() == '+' || ss.peek() == '*') {
            char op;

            while (ss >> op) {
                ops.push_back(op);
            }
        } else {
            while (ss >> num) {
                num_line.push_back(num);
            }

            grid.push_back(std::move(num_line));
        }
    }

    long long res = 0;
    for (int i = 0; i < ops.size(); i++) {
        res += solve_problem(i, ops[i], grid);
    }

    std::cout << res << '\n';
    return 0;
}