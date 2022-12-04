/**
 * Author: Bikmetov Shakir
 * License: CC0
 * Description: Sub over subset DP
 * Time: O(N * 2^N) for N bit masks
 */

constexpr int MAX_BITS = 22;
constexpr int MAX_N = 1ll << MAX_BITS;

int a[MAX_N];
int f[MAX_N];

void sos_dp() {
    rep(i, 0, MAX_N)
        f[i] = a[i];
  
    for (int j = 0; j < MAX_BITS; j++) {
        for (int i = 0; i < MAX_N; i++) {
            if (i & (1 << j)) {
                // use any commutative operation
                f[i] += f[i ^ (1 << j)];
            }
        }
    }
}