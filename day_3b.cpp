#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

long long get_max_joltage(const std::string& bank_str) {
    int bank_size = bank_str.length();
    std::vector<int> bank(bank_size);

    int i = 0;
    for (char c : bank_str) {
        bank[i++] = c - '0';
    }

    std::vector<int> v;
    for (int i = bank_size - 12; i < bank_size; i++) {
        v.push_back(bank[i]);
    }

    for (int i = bank_size - 13; i >= 0; i--) {
        if (bank[i] >= v[0]) {
            for (int j = 1; j < 12; j++) {
                if (v[j] > v[j - 1]) {
                    v.erase(v.begin() + j - 1);
                    break;
                }
            }

            if (v.size() == 12) {
                v.erase(v.begin() + 11);
            }
            v.insert(v.begin(), bank[i]);
        }
    }

    long long max_jolt = 0;
    for (int bat : v) {
        max_jolt = max_jolt * 10 + bat;
    }
    std::cout << max_jolt << std::endl;
    return max_jolt;
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::string bank;
    long long total_joltage = 0;
    while (std::getline(input_file, bank)) {
        total_joltage += get_max_joltage(bank);
    }

    std::cout << total_joltage << '\n';

    return 0;
}
