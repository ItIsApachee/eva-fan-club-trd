/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: Hashing for strings.
 * Time: O(N) for construction, O(1) query
 */

#pragma once

template <ull Prime, ull Mod>
struct Hash {
    vector<ull> hash;
    inline static vector<ull> pow = {1};

    Hash(string s) : hash(s.size() + 1, 0) {
        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i]*Prime + s[i]) % Mod;
        }
        if (pow.size() < s.size() + 1) {
            int old_sz = pow.size();
            pow.resize(s.size() + 1);
            for (int i = old_sz; i < pow.size(); i++) {
                pow[i] = pow[i - 1] * Prime % Mod;
            }
        }
    }
    ull substr(int pos, int len) {
        ull r = Mod - (hash[pos] * pow[len] % Mod);
        r = hash[pos + len] + r;
        if (r >= Mod)
            r -= Mod;
        assert(r < Mod);
        return r;
    }
    static ull full_hash(string s) {
        if (pow.size() < s.size() + 1) {
            int old_sz = pow.size();
            pow.resize(s.size() + 1);
            for (int i = old_sz; i < pow.size(); i++) {
                pow[i] = pow[i - 1] * Prime % Mod;
            }
        }

        ull r = 0;
        for (int i = 0; i < s.size(); i++) {
            r = (r*Prime + s[i]) % Mod;
        }
        return r;
    }
};

typedef Hash<31, 1000*1000*1000+7> H;
typedef Hash<31, 1000*1000*1000+7> H1;
typedef Hash<97, 1000*1000*1000+123> H2;

struct DHash {
    H1 h1;
    H2 h2;
    DHash(string s): h1(s), h2(s) {}
    pair<ull, ull> substr(int pos, int len) {
        return make_pair(h1.substr(pos, len), h2.substr(pos, len));
    }
    static pair<ull, ull> full_hash(string s) {
        return make_pair(H1::full_hash(s), H2::full_hash(s));
    }
};