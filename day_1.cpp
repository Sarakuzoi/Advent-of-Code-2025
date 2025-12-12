#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream InputFile("input.in");
    if (!InputFile) {
        cerr << "Cannot open input.in\n";
        return 1;
    }

    string rotation;
    long long current = 50;
    long long zeroes_method2 = 0;

    while (getline(InputFile, rotation)) {
        if (rotation.empty()) continue;
        char dir = rotation[0];
        long long steps = stoll(rotation.substr(1));
        long long start = current;

        if (dir == 'R') {
            long long d = steps;
            if (start == 0) {
                zeroes_method2 += d / 100;
            } else {
                long long first = 100 - start;
                if (d >= first) {
                    zeroes_method2 += 1 + (d - first) / 100;
                }
            }
            current = (start + d) % 100;
        } else {  // 'L'
            long long d = steps;
            if (start == 0) {
                zeroes_method2 += d / 100;
            } else {
                long long first = start;
                if (d >= first) {
                    zeroes_method2 += 1 + (d - first) / 100;
                }
            }
            current = ((start - d) % 100 + 100) % 100;
        }
    }

    cout << zeroes_method2 << '\n';
    return 0;
}
