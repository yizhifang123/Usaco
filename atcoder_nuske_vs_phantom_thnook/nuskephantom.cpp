#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    vector<tuple<int, int, int, int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        queries[i] = make_tuple(x1, y1, x2, y2);
    }

    // 1-based indexing for prefix sums
    vector<vector<int>> B(N+1, vector<int>(M+1, 0)); // blue squares
    vector<vector<int>> H(N+1, vector<int>(M+1, 0)); // horizontal blue edges
    vector<vector<int>> V(N+1, vector<int>(M+1, 0)); // vertical blue edges

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            B[i][j] = B[i-1][j] + B[i][j-1] - B[i-1][j-1] + (grid[i-1][j-1] == '1');
            H[i][j] = H[i-1][j] + H[i][j-1] - H[i-1][j-1];
            V[i][j] = V[i-1][j] + V[i][j-1] - V[i-1][j-1];
            if (j < M && grid[i-1][j-1] == '1' && grid[i-1][j] == '1') {
                H[i][j] += 1;
            }
            if (i < N && grid[i-1][j-1] == '1' && grid[i][j-1] == '1') {
                V[i][j] += 1;
            }
        }
    }
    // // Print prefix sums for debugging
    // cout << "Prefix sum of blue squares (B):" << endl;
    // for (int i = 0; i <= N; ++i) {
    //     for (int j = 0; j <= M; ++j) {
    //         cout << B[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Prefix sum of horizontal blue edges (H):" << endl;
    // for (int i = 0; i <= N; ++i) {
    //     for (int j = 0; j <= M; ++j) {
    //         cout << H[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Prefix sum of vertical blue edges (V):" << endl;
    // for (int i = 0; i <= N; ++i) {
    //     for (int j = 0; j <= M; ++j) {
    //         cout << V[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for (const auto& q : queries) {
        int x1, y1, x2, y2;
        tie(x1, y1, x2, y2) = q;

        // Number of blue squares in the region
        int S = B[x2][y2] - B[x1-1][y2] - B[x2][y1-1] + B[x1-1][y1-1];

        // Number of horizontal blue edges in the region
        int H_sum = H[x2][y2-1] - H[x1-1][y2-1] - H[x2][y1-1] + H[x1-1][y1-1];

        // Number of vertical blue edges in the region
        int V_sum = V[x2-1][y2] - V[x1-1][y2] - V[x2-1][y1-1] + V[x1-1][y1-1];

        // Number of blue components = blue squares - blue edges
        int answer = S - (H_sum + V_sum);

        cout << answer << '\n';
    }
    return 0;
}
