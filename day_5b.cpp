#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

struct Interval {
    long long start;
    long long end;
};

std::vector<Interval> get_merged_intervals(std::vector<Interval>& intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](const Interval& a, const Interval& b) {
                  return (a.start != b.start) ? a.start < b.start
                                              : a.end < b.end;
              });

    std::vector<Interval> merged_intervals;
    for (const auto& i : intervals) {
        if (merged_intervals.size() == 0) {
            merged_intervals.push_back(i);
            continue;
        }

        if (i.start <= merged_intervals.back().end + 1) {
            Interval& last = merged_intervals.back();
            last.end = std::max(last.end, i.end);
        } else {
            merged_intervals.push_back(i);
        }
    }

    return merged_intervals;
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Cannot open input file!";
        return 1;
    }

    std::string line;
    std::vector<Interval> intervals;
    std::vector<long long> ids;
    while (getline(input_file, line)) {
        if (line.length() == 0) break;
        long long start, end;
        char dash;
        std::stringstream ss(line);

        ss >> start >> dash >> end;
        intervals.push_back({start, end});
    }
    intervals = get_merged_intervals(intervals);

    long long fresh_ingredients = 0;
    for (const auto& i : intervals) {
        fresh_ingredients += i.end - i.start + 1;
    }

    std::cout << fresh_ingredients << '\n';

    return 0;
}
