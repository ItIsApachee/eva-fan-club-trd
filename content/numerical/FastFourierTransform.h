/**
 * License: CC0
 * Description: Fast Fourier Transform with linear reverse precalc.
 * Author: Shakir Bikmetov
 * Time: O(N \log N)
 */
#pragma once

#include "FFTRevPrecalc.h"

using base_float = double;
using base = complex<base_float>;
const base_float PI = acosl(-1.0);

// n = 2^i
void fft(vector<base> &a, int n, bool invert) {
	rev_precalc(__lg(n));
	for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int len = 1; len < n; len <<= 1) {
        int len2 = len << 1;
        base_float angle = 2.0l*PI/(base_float)len2;
        if (invert)
            angle = -angle;
        for (int i = 0; i < n; i += len2) {
            for (int j = 0; j < len; j++) {
                base wj = exp(base{0.0l, angle*j});
                base x = a[i + j], y = a[i + j + len];
                y *= wj;
                a[i + j] = x + y;
                a[i + j + len] = x - y;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }
}