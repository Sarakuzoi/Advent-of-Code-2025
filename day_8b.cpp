#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <ranges>
#include <sstream>
#include <vector>

struct Box {
    int x, y, z;
};
struct Edge {
    int start, end;
    long long dist_sq;
};

class UnionFind {
    std::vector<int> parent;

   public:
    explicit UnionFind(size_t size) : parent(size) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return (parent[x] == x) ? x : (parent[x] = find(parent[x]));
    }

    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) parent[rootX] = rootY;
    }

    size_t size() const { return parent.size(); }
};

long long dist_sq(const Box& a, const Box& b) {
    auto dx = a.x - b.x;
    auto dy = a.y - b.y;
    auto dz = a.z - b.z;
    return 1LL * dx * dx + 1LL * dy * dy + 1LL * dz * dz;
}

std::optional<long long> get_mst_connections_prod(std::vector<Edge>& edges,
                                                  std::vector<Box>& boxes,
                                                  int num_connections) {
    std::sort(edges.begin(), edges.end(),
              [](Edge& a, Edge& b) { return a.dist_sq < b.dist_sq; });

    auto uf = UnionFind(boxes.size());
    int clusters = boxes.size();

    for (const auto& [start, end, _] : edges) {
        if (uf.find(start) != uf.find(end)) {
            uf.merge(start, end);
            clusters--;
        }
        if (clusters == 1) {
            return 1LL * boxes[start].x * boxes[end].x;
        }
    }

    return std::nullopt;
}

int main() {
    std::ifstream input_file("input.in");
    if (!input_file) {
        std::cerr << "Error: Could not open input.in\n";
        return 1;
    }

    std::string line;
    std::vector<Box> boxes;
    while (getline(input_file, line)) {
        std::stringstream ss(line);

        int x, y, z;
        char comma;
        ss >> x >> comma >> y >> comma >> z;
        boxes.push_back({x, y, z});
    }

    std::vector<Edge> edges;
    edges.reserve(boxes.size() * boxes.size() / 2);
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i + 1; j < boxes.size(); j++) {
            edges.push_back({i, j, dist_sq(boxes[i], boxes[j])});
        }
    }

    auto res = get_mst_connections_prod(edges, boxes, 1000);
    if (res.has_value())
        std::cout << res.value() << "\n";
    else
        std::cout << "No solution found\n";

    return 0;
}