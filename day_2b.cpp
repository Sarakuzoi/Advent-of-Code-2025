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
        for (long long num_ll = range.start; num_ll <= range.end; ++num_ll) {
            std::string num = std::to_string(num_ll);
            int length = num.length();

            for (int curr = 1; curr <= length / 2; curr++) {
                if (length % curr != 0) continue;

                std::string orig = num.substr(0, curr);
                bool invalid = true;
                for (int ptr = 0; ptr <= length - curr; ptr += curr) {
                    // std::cout << num.substr(ptr, curr) << std::endl;
                    if (num.substr(ptr, curr) != orig) {
                        invalid = false;
                        break;
                    }
                }

                if (invalid) {
                    std::cout << "Adding " << num_ll << std::endl;
                    invalid_ids_sum += num_ll;
                    break;
                }
            }
        }
    }

    std::cout << invalid_ids_sum;
    return 0;
}
