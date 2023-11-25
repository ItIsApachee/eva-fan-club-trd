/**
 * Author: Bikmetov Shakir
 * License: CC0
 * Description: Ring of integers modulo MOD
 */

constexpr int MOD = 1e9 + 7;

struct Mint {
    ll v{0};
 
    Mint() = default;
    Mint(ll v, bool divide = true): v{((v % MOD) + MOD) % MOD} {}
    Mint& operator=(const Mint&) = default;
 
    Mint operator+() const {
        return *this;
    }
    Mint operator-() const {
        Mint res = 0;
        return res -= *this;
    }
    Mint& operator+=(const Mint& rhs) {
        v = (v + rhs.v) % MOD;
        return *this;
    }
    Mint& operator-=(const Mint& rhs) {
        v = (v + MOD - rhs.v) % MOD;
        return *this;
    }
    Mint& operator*=(const Mint& rhs) {
        v = v * rhs.v % MOD;
        return *this;
    }
    Mint& operator/=(const Mint& rhs) {
        return *this *= rhs.inverse();
    }

    Mint binpow(ll p) const {
        Mint r = 1;
        Mint a = *this;
 
        while (p) {
            if (p % 2 == 1)
                r *= a;
            a *= a;
            p /= 2;
        }
        return r;
    }
 
    Mint inverse() const {
        return this->binpow(MOD - 2);
    }
};
Mint operator+(const Mint &a, const Mint &b) {
    Mint r = a;
    return r += b;
}
Mint operator-(const Mint &a, const Mint &b) {
    Mint r = a;
    return r -= b;
}
Mint operator*(const Mint &a, const Mint &b) {
    Mint r = a;
    return r *= b;
}
Mint operator/(const Mint &a, const Mint &b) {
    Mint r = a;
    return r /= b;
}
