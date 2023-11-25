/**
 * Author: Bikmetov Shakir
 * License: CC0
 * Description: Find centroid
 * Time: O(N log N)
 */

#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (int i = a; i < b; i++)

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr char LF = '\n';
constexpr char SP = ' ';

constexpr int MAX_N = 1e5;
vector<int> g[MAX_N];

int clvl[MAX_N];

int curr_lvl;
int get_sz(int v, int p) {
    int sz = 0;
    for (auto to : g[v]) {
        if (to == p || clvl[to] < curr_lvl)
            continue;
        sz += get_sz(to, v);
    }
    return 1 + sz;
}

// {sz, false}
// {center, true}
int curr_lvl_sz;
pair<int, bool> find_center(int v, int p) {
    int sz = 1;
    int max_sz = 0;
    for (auto to : g[v]) {
        if (to == p || clvl[to] < curr_lvl)
            continue;
        auto to_val = find_center(to, v);
        if (to_val.second)
            return to_val;
        max_sz = max(max_sz, to_val.first);
        sz += to_val.first;
    }
    if (sz > curr_lvl_sz / 2 && max_sz <= curr_lvl_sz / 2)
        return {v, true};
    return {sz, false};
}

void centroid(int v = 0, int lvl = 0) {
    curr_lvl = lvl;
    curr_lvl_sz = get_sz(v, -1);

    auto center_ = find_center(v, -1);
    assert(center_.second);
    int center = center_.first;

    clvl[center] = lvl;
    for (auto to : g[center]) {
        if (clvl[to] > clvl[center])
            centroid(to, lvl + 1);
    }
}

// centroid(0, 0) finds all centroids