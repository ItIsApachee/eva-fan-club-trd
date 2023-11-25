/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: FFT in GF(998'244'353)
 * Time: O(N log N)
 */

#include <bits/stdc++.h>

#include "FFTRevCalc.h"

using namespace std;
using base_t = int;

constexpr int MOD = 998'244'353;
constexpr int ROOT = 31;
constexpr int ROOT_INV = 128805723;
constexpr int ROOT_LOG2_DEG = 23;

int binpow(int a, int power) {
    int r = 1;
    while (power) {
        if (power % 2)
            r = r * 1ll * a % MOD;
        a = a * 1ll * a % MOD;
        power /= 2;
    }
    return r;
}

int inverse(int a) {
    return binpow(a, MOD - 2);
}

int get_root(int deg, bool inv) {
    int log2_deg = __lg(deg);
    return binpow(inv ? ROOT_INV : ROOT, 1 << (ROOT_LOG2_DEG - log2_deg));
}

void fft(vector<base_t>& a, bool inv_flag = false) {
    assert((1 << __lg(a.size())) == a.size());
    int n = a.size();
    int n_bits = __lg(n);
    rev_calc(n_bits);
    for (int i = 0; i < n; i++) {
        auto i_rev = rev_precalc[n_bits][i];
        if (i < i_rev)
            swap(a[i], a[i_rev]);
    }

    for (int k = 2; k <= n; k *= 2) {
        int k_half = k / 2;

        base_t w0 = get_root(k, inv_flag);
        for (int i = 0; i < n; i += k) {
            base_t w = 1;
            for (int j = 0; j < k_half; j++, w = w * 1ll * w0 % MOD) {
                base_t x = a[i + j], y = a[i + j + k_half];
                y = (y * 1ll * w) % MOD;
                a[i + j] = (x + y) % MOD, a[i + j + k_half] = (x - y + MOD) % MOD;
            }
        }
    }

    if (inv_flag) {
        int n_inv = inverse(n);
        for (int i = 0; i < n; i++)
            a[i] = a[i] * 1ll * n_inv % MOD;
    }
}