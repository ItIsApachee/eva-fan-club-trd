/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: Hashing for submatrixes.
 * Time: O(N*M) for construction, O(1) query
 */

#pragma once

#include "Hash.h"

template <ull Mod, ull PrimeP, ull PrimeQ>
struct Hash2d {
    vector<vector<ull>> hash;
    inline static vector<ull> pow_col = {1};

    using Hasher = Hash<PrimeP, Mod>;

    Hash2d(const vector<string> &arr) {
        int n = arr.size();
        int m = arr[0].size();

        hash.assign(n + 1, vector<ull> (m + 1, 0));
        for (int i = 0; i < n; i++) {
            Hasher h(arr[i]);
            for (int j = 0; j < m; j++) {
                hash[i + 1][j + 1] = (hash[i][j + 1] * PrimeQ + h.hash[j + 1]) % Mod;
            }
        }

        if (pow_col.size() < n + 1) {
            int old_sz = pow_col.size();
            pow_col.resize(n + 1);
            for (int i = old_sz; i < pow_col.size(); i++) {
                pow_col[i] = pow_col[i - 1] * PrimeQ % Mod;
            }
        }
    }
    ull substr(int y, int x, int n, int m) {
        ull r = hash[y + n][x + m];
        r += pow_col[n] * Hasher::pow[m] % Mod * hash[y][x] % Mod;
        r += Mod - (pow_col[n] * hash[y][x + m] % Mod);
        r += Mod - (Hasher::pow[m] * hash[y + n][x] % Mod);
        r %= Mod;
        return r;
    }
};

template <class H1, class H2>
struct DHash2d {
    H1 h1;
    H2 h2;

    DHash2d(const vector<string> &arr) : h1(arr), h2(arr) {}
    pair<ull, ull> substr(int y, int x, int n, int m) {
        return make_pair(h1.substr(y, x, n, m), h2.substr(y, x, n, m));
    }
};

using H = DHash2d<Hash2d<1000*1000*1000+7, 31, 65537>, Hash2d<1000*1000*1000+123, 239, 29>>;