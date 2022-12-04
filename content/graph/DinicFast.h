/**
 * Author: Shakir Bikmetov
 * License: CC0
 * Description: Dinic as taught by Andrew Stankevich.
 * Time: O(VE \log C_{max})
 */
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr char LF = '\n';
constexpr char SP = ' ';

constexpr int INF = 1e9 + 100;
constexpr int MAX_N = 500;

struct Edge {
    int u, v, c;
    int f{0};

    inline int can() {
        return c - f;
    }
};

vector<Edge> edges;
vector<int> g[MAX_N];

int s, t;
int BOUND = 1;

array<int, MAX_N> dist;
bool bfs() {
    queue<int> q;
    fill(dist.begin(), dist.end(), MAX_N);
    dist[s] = 0;
    q.push(s);

    while (q.size()) {
        int v = q.front();
        q.pop();

        for (auto eid: g[v]) {
            auto &e = edges[eid];
            if (dist[e.v] == MAX_N && e.can() >= BOUND) {
                dist[e.v] = dist[v] + 1;
                q.push(e.v);
            }
        }
    }

    return dist[t] != MAX_N;
}

bitset<MAX_N> vis;
array<int, MAX_N> edge_cnt;
int dfs(int v, int minc) {
    vis[v] = true;

    if (v == t)
        return minc;

    for (; edge_cnt[v] < g[v].size(); edge_cnt[v]++) {
        int eid = g[v][edge_cnt[v]];
        auto &e = edges[eid];
        if (!vis[e.v] && e.can() >= BOUND && dist[e.v] == dist[v] + 1) {
            int r = dfs(e.v, min(minc, e.can()));
            if (r > 0) {
                auto &er = edges[eid ^ 1];
                e.f += r;
                er.f -= r;
                return r;
            }
        }
    }

    return 0;
}

ll dinic() {
    ll ans = 0;
    for (BOUND = 1 << 30; BOUND > 0; BOUND /= 2) {
        while (bfs()) {
            fill(edge_cnt.begin(), edge_cnt.end(), 0);
            while (true) {
                vis.reset();
                int r = dfs(s, INF);
                ans += r;
                if (r == 0)
                    break;
            }
        }
    }
    return ans;
}

void add_edge(int u, int v, int c1, int c2 = 0) {
    g[u].push_back(edges.size());
    edges.push_back(Edge{u, v, c1});
    g[v].push_back(edges.size());
    edges.push_back(Edge{v, u, c2});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        add_edge(u, v, c);
    }

    s = 0;
    t = n - 1;

    ll ans = dinic();
    cout << ans << LF;
    for (int i = 0; i < m; i++) {
        cout << edges[2*i].f << LF;
    }
}