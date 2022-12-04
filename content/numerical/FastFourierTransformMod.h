/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: FFT in GF(Prime). Uses inverse(w) to calculate $w^{-1}$, and binpow(a, p) to calculate $a^p$.
 * Time: O(N \log N)
 */
#pragma once

#include "FFTRevPrecalc.h"

constexpr ll MOD = 998244353;
// 2^ROOT_DEG-th root of 1 modulo MOD
constexpr ll MOD_ROOT = 31;
constexpr ll ROOT_DEG = 23;

ll get_root(ll lg_deg) {
    return binpow(MOD_ROOT, 1ll << (ROOT_DEG - lg_deg));
}

// n = 2^i
void fft(vector<ll> &a, int n, bool invert) {
	rev_precalc(__lg(n));
	for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }

    for (ll len = 1; len < n; len <<= 1) {
        ll len2 = len << 1;
        ll w = get_root(__lg(len2));
        if (invert)
            w = inverse(w); // w^-1
        for (int i = 0; i < n; i += len2) {
            ll wj = 1;
            for (int j = 0; j < len; j++) {
                ll x = a[i + j], y = a[i + j + len];
                y = (y * wj) % MOD;
                a[i + j] = (x + y) % MOD;
                a[i + j + len] = (x - y + MOD) % MOD;
                wj = (wj * w) % MOD;
            }
        }
    }
    if (invert) {
        ll n_inv = inverse(n); // n^-1
        for (int i = 0; i < n; i++)
            a[i] = (a[i] * n_inv) % MOD;
    }
}