#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct Wormhole {
    int a, b, width;
};

class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

bool canSort(int n, const vector<int>& positions, const vector<Wormhole>& wormholes, int minWidth) {
    UnionFind uf(n + 1); // 1-indexed

    // Add all wormholes with width >= minWidth
    for (const auto& wh : wormholes) {
        if (wh.width >= minWidth) {
            uf.unite(wh.a, wh.b);
        }
    }

    // Check if each cow can reach its target position
    for (int i = 1; i <= n; i++) {
        if (!uf.connected(positions[i-1], i)) {
            return false;
        }
    }

    return true;
}

int main() {
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");

    int n, m;
    fin >> n >> m;

    vector<int> positions(n);
    for (int i = 0; i < n; i++) {
        fin >> positions[i];
    }

    // Check if already sorted
    bool alreadySorted = true;
    for (int i = 0; i < n; i++) {
        if (positions[i] != i + 1) {
            alreadySorted = false;
            break;
        }
    }

    if (alreadySorted) {
        fout << -1 << endl;
        return 0;
    }

    vector<Wormhole> wormholes(m);
    for (int i = 0; i < m; i++) {
        fin >> wormholes[i].a >> wormholes[i].b >> wormholes[i].width;
    }

    // Binary search on the answer
    int left = 1, right = 1000000000;
    int answer = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canSort(n, positions, wormholes, mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    fout << answer << endl;

    return 0;
}