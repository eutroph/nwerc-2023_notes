/**
 * Author: Joshua Chen
 * Date: 2024-03-19
 * License: CC0
 * Description: Perform flow with demands on each edge. 
 * To minimise flow, binary search on the lowest weight from sink to source that yields a valid flow.
 * Time:$O(V^2\sqrt E)$
 * Status: Tested on https://codeforces.com/gym/100199
 */
#pragma once

#include "PushRelabel.h"

struct FlowDemands {
    vector<ll> ind, outd;
    map<pair<int, int>, ll> m;
    int n;
    ll D;
    PushRelabel g;
    FlowDemands(int _n) : n(_n), D(0), ind(vector<ll>(_n)), outd(vector<ll>(_n)), g(PushRelabel(_n+2)) {}
    void addEdge(int s, int t, ll cap, ll demand) {
        g.addEdge(s, t, cap - demand);
        D += demand;
        ind[t] += demand;
        outd[s] += demand;
        m[{s, t}] = demand;
    }
    pair<bool, vector<pair<pair<int, int>, ll>>> solve(int source, int sink) {
        g.addEdge(sink, source, LLONG_MAX);
        rep(i, 0, n) {
            if (ind[i]) g.addEdge(n, i, ind[i]);
            if (outd[i]) g.addEdge(i, n+1, outd[i]);
        }
        if (g.calc(n, n+1) != D) return {false, {}};
        vector<pair<pair<int, int>, ll>> res;
        rep(i, 0, n) {
            for (auto e : g.g[i]) {
                if (e.dest < n && e.f > 0) m[{i, e.dest}] += e.f;
            }
        }
        for (auto [x, y] : m) res.push_back({x, y});
        return {true, res};
    }
};