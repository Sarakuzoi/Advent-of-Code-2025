#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
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

int get_n_biggest_clusters_prod(UnionFind& uf, int n) {
    std::vector<int> cluster_sizes(uf.size(), 0);
    for (int i = 0; i < uf.size(); ++i) {
        cluster_sizes[uf.find(i)]++;
    }

    std::ranges::sort(cluster_sizes, std::greater<>{});

    int product = 1;
    for (int size : cluster_sizes | std::views::take(n)) {
        std::cout << size << ' ';
        product *= size;
    }
    return product;
}

int get_mst_connections_prod(std::vector<Edge>& edges, std::vector<Box>& boxes,
                             int num_connections) {
    std::sort(edges.begin(), edges.end(),
              [](Edge& a, Edge& b) { return a.dist_sq < b.dist_sq; });

    auto uf = UnionFind(boxes.size());
    int connections = 0;

    for (const auto& [start, end, _] : edges) {
        connections++;

        if (uf.find(start) != uf.find(end)) {
            uf.merge(start, end);
        }

        if (connections == num_connections) {
            return get_n_biggest_clusters_prod(uf, 3);
        }
    }

    return -1;
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
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i + 1; j < boxes.size(); j++) {
            edges.push_back({i, j, dist_sq(boxes[i], boxes[j])});
        }
    }

    std::cout << get_mst_connections_prod(edges, boxes, 1000) << '\n';

    return 0;
}