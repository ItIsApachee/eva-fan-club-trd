/**
 * License: CC0
 * Description: Linear reverse precalc for FFT.
 * Author: Shakir Bikmetov
 * Time: O(N)
 */
constexpr int MAX_BITS = /* specify this number */;

int rev[1 << MAX_BITS];

// n = 2^i
void rev_precalc(int n) {
	int bits = __lg(n);
	assert(bits <= MAX_BITS);
    for (int l = bits - 1, step = 1; step < n; l--, step *= 2) {
        int v = 1 << l;
        for (int i = step; i < n; i += step) {
            rev[i] ^= v;
        }
    }
    for (int i = 1; i < n; i++) {
        rev[i] ^= rev[i - 1];
    }
}