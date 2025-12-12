#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int get_max_joltage(const std::string& bank_str) {
    int bank_size = bank_str.length();
    std::vector<int> bank(bank_size);

    int i = 0;
    for (char c : bank_str) {
        bank[i++] = c - '0';
    }

    int max_right = bank[bank_size - 1];
    int max_jolt = -1;
    for (int i = bank_size - 2; i >= 0; i--) {
        max_jolt = std::max(max_jolt, bank[i] * 10 + max_right);
        max_right = std::max(max_right, bank[i]);
    }

    return max_jolt;
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::string bank;
    int total_joltage = 0;
    while (std::getline(input_file, bank)) {
        total_joltage += get_max_joltage(bank);
    }

    std::cout << total_joltage << '\n';

    return 0;
}
