#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<long long> A(M+1, 0), B(M+1, 0);
    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        ++A[a];
        ++B[b];
    }
    int L = 2 * M;
    vector<long long> S(L+1, 0), E(L+1, 0);
    // Convolution A*A -> S, and B*B -> E
    for (int x = 0; x <= M; ++x) {
        if (A[x] != 0) {
            for (int y = 0; y <= M; ++y) {
                if (A[y] != 0) {
                    S[x + y] += A[x] * A[y];
                }
            }
        }
        if (B[x] != 0) {
            for (int y = 0; y <= M; ++y) {
                if (B[y] != 0) {
                    E[x + y] += B[x] * B[y];
                }
            }
        }
    }
    // Prefix sums
    vector<long long> prefS(L+1, 0), prefE(L+1, 0);
    prefS[0] = S[0];
    prefE[0] = E[0];
    for (int t = 1; t <= L; ++t) {
        prefS[t] = prefS[t-1] + S[t];
        prefE[t] = prefE[t-1] + E[t];
    }
    // Output answers for k = 0..2M
    for (int k = 0; k <= L; ++k) {
        long long lessE = (k == 0) ? 0LL : prefE[k-1];
        long long ans = prefS[k] - lessE;
        cout << ans << '\n';
    }
    return 0;
}
