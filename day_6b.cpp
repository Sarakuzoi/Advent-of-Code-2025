#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::pair<long long, int> solve_problem(int js, char op,
                                        const std::vector<std::string>& grid) {
    long long res = op == '*' ? 1 : 0;
    int last_j = -1;
    for (int j = js; j < grid[0].size(); j++) {
        int curr_num = 0;
        int found_digit = false;
        for (int i = 0; i < grid.size(); i++) {
            if (isdigit(grid[i][j])) {
                found_digit = true;
                curr_num = curr_num * 10 + (grid[i][j] - '0');
            }
        }
        if (!found_digit) {
            last_j = j;
            break;
        }
        res = op == '*' ? (res * curr_num) : (res + curr_num);
    }

    return {res, last_j};
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::vector<std::string> grid;
    std::vector<char> ops;
    std::string line;
    while (getline(input_file, line)) {
        std::stringstream ss(line);
        std::string num;

        if (ss.peek() == '+' || ss.peek() == '*') {
            char op;

            while (ss >> op) {
                ops.push_back(op);
                if (ss.peek() == ' ') continue;
            }
        } else {
            grid.push_back(std::move(line));
        }
    }

    long long res = 0;
    int op_idx = 0;
    for (int j = 0; j < grid[0].size(); j++) {
        auto [prob_res, nj] = solve_problem(j, ops[op_idx], grid);
        res += prob_res;
        if (nj == -1) break;
        j = nj;
        op_idx++;
    }

    std::cout << res << '\n';
    return 0;
}