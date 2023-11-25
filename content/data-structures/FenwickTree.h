/**
 * Author: Bikmetov Shakir
 * License: CC0
 * Description: Sub over subset DP
 * Time: O(log(n)) any request
 */

int f[MAXN]; // 1-indexed
void upd(int x, int add) {
    for (int i = x; i < MAXN; i += i & -i)
        f[i] += add;
}

int get(int x) {
    int res = 0;
    for (int i = x; i > 0; i -= i & -i)
        res += f[i];
    return res;
}