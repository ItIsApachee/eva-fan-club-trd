/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: FFT with floats
 * Time: O(N log N)
 */

#include <bits/stdc++.h>

#include "FFTRevCalc.h"

using namespace std;

using base_float = double;
using base_t = complex<base_float>;

base_float PI = acosl(-1);

void fft(vector<base_t>& a, bool inverse = false) {
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

        base_float power = 2 * (inverse ? -1 : 1) * PI / k;
        base_t w0 = exp(base_t{0.0L, power});
        for (int i = 0; i < n; i += k) {
            base_t w = 1;
            for (int j = 0; j < k_half; j++, w *= w0) {
                base_t x = a[i + j], y = a[i + j + k_half];
                y *= w;
                a[i + j] = x + y, a[i + j + k_half] = x - y;
            }
        }
    }

    if (inverse) {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }
}