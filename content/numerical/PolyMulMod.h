/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: Polynomial mult.
 */
#include "FFTMod.h"

vector<int> polymult(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    int m = b.size();
    int sz = 1 << (1 + __lg((n + m) - 1));

    vector<base_t> ac(sz);
    copy(a.begin(), a.end(), ac.begin());
    vector<base_t> bc(sz);
    copy(b.begin(), b.end(), bc.begin());

    fft(ac);
    fft(bc);
    for (int i = 0; i < sz; i++) ac[i] = (ac[i] * 1ll * bc[i]) % MOD;
    fft(ac, true);

    while (ac.size() > 1 && ac.back() == 0)
        ac.pop_back();

    vector<int> result(ac.size());
    transform(ac.begin(), ac.end(), result.begin(), [](const base_t& v) {
        if (v > MOD / 2)
            return v - MOD;
        else
            return v;
    });
    return result;
}