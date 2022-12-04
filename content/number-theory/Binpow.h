/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: Binary exponentiation modulo MOD
 * Time: O(\log (power))
 */

constexpr ll MOD = 1000000007;

ll binpow(ll a, ll p) {
	ll res = 1;
	for (; e; a = a * a % MOD, p /= 2)
		if (e & 1) res = res * b % MOD;
	return res;
}

// inverse modulo prime
ll inverse(ll a) {
    return binpow(a, MOD - 2);
}