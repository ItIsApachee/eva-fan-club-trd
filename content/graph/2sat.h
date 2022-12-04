/**
 * Author: Sergey Panin
 * License: CC0
 * Description: 2-SAT.	
 * Time: ???
 */
#pragma once

#include <bits/stdc++.h>

#define eps 10e-7
#define ll long long
#define pb push_back
#define all(x) (x).begin(),(x).end()
 
using namespace std;
 
vector <vector <int>> g, gt;
vector <bool> used;
vector <int> topsort, comp;
 
void dfs1(int v) {
    used[v] = true;
    for (auto to : g[v])
        if (!used[to])
            dfs1(to);
    topsort.pb(v);
}
 
void dfs2(int v, int cl) {
    comp[v] = cl;
    for (auto to : gt[v])
        if (comp[to] == -1)
            dfs2(to, cl);
}
 
 
int main()
{
    int n, m; // m - number of vertices
    cin >> n >> m;

    g.resize(2*m); // direct graph
    gt.resize(2*m); // inverse graph

    // graph construction
    // (a || b) && (b || !c)
    // edges
    // !a => b
    // !b => a
    // !b => !c
    // c => b
    vector <int> res(m);
    for (int i = 0; i < 2*m; i++) {
        for (auto item : g[i]) {
            gt[item].pb(i);
        }
    }
 
    used.assign(2*m, false);
    for (int i = 0; i < 2*m; i++)
        if (!used[i])
            dfs1(i);
 
    comp.assign(2*m, -1);
 
    reverse(all(topsort));
 
    for (int i = 0, j = 0; i < 2*m; i++) {
        int v = topsort[i];
        if (comp[v] == -1) {
            dfs2(v, j);
            j++;
        }
    }
 
    for (int i = 0; i < m; i++) {
        if (comp[2*i] == comp[2*i + 1] && comp[2*i + 1] != -1) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
 
    for (int i = 0; i < m; i++) {
        if (comp[2*i] == -1) {
            res[i] = true;
            continue;
        }
        if (comp[2*i] > comp[2*i + 1])
            res[i] = true;
        else
            res[i] = false;
    }
    return 0;
}