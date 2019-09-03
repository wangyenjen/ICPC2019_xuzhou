#include <testlib.h>

#include <numeric>
#include <vector>
#include <utility>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int m = atoi(argv[1]);

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = rnd.next(n);
        int v = rnd.next(n);
        edges.emplace_back(u, v);
    }

    println(n, edges.size());
    for (auto edge : edges)
        println(edge.first + 1, edge.second + 1);
}
