#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct interval {
    long long start;
    long long end;
};

int main() {
    std::ifstream InputFile("input.in");
    if (!InputFile) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::string input;
    std::getline(InputFile, input);
    input += ",";

    std::stringstream ss(input);
    std::vector<interval> ranges;

    long long start, end;
    char dash, comma;

    while (ss >> start >> dash >> end) {
        ranges.push_back({start, end});
        if (ss.peek() == ',') {
            ss >> comma;
        }
    }

    long long invalid_ids_sum = 0;
    for (const auto& range : ranges) {
        for (long long num = range.start; num <= range.end; ++num) {
            int length = (num == 0) ? 1 : static_cast<int>(std::log10(num)) + 1;

            // We only care if the length is even (e.g., 2, 4, 6 digits)
            if (length % 2 != 0) continue;

            long long half_len = length / 2;
            long long divisor = pow(10, half_len);

            long long first_half = num / divisor;
            long long second_half = num % divisor;

            if (first_half == second_half) {
                invalid_ids_sum += num;
            }
        }
    }

    std::cout << invalid_ids_sum;
    return 0;
}
