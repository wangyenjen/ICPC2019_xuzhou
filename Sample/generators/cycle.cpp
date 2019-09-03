#include <testlib.h>

#include <numeric>
#include <vector>
#include <utility>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);

    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        int u = perm[i];
        int v = perm[(i + 1) % n];

        if (rnd.next(2))
            std::swap(u, v);

        edges.emplace_back(u, v);
    }
    shuffle(edges.begin(), edges.end());

    println(n, edges.size());
    for (auto edge : edges)
        println(edge.first + 1, edge.second + 1);
}
