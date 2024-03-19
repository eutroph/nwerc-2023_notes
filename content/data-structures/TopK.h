/**
 * Author: Joshua Chen
 * Date: 2024-03-19
 * Description: Add/remove elements, keep track of sum of smallest or largest K elements.
 * Time: $O(\log N)$
 */

#pragma once

template <class Compare = less<ll>> struct topK {
    multiset<ll, Compare> s;
    int k;
    ll total = 0;
    typename multiset<ll, Compare>::iterator it;

    topK() {}
    topK(int _k) : k(_k) {}

    void insert(ll x) {
        s.insert(x);
        if (s.size() <= k) total += x;
        else if (Compare{}(x, *it)) total += x - *it--;
        if (s.size() == k) it = prev(s.end());
    }

    void erase(ll x) {
        if (s.size() <= k) s.erase(s.lower_bound(x)), total -= x;
        else {
            auto it2 = s.lower_bound(x);
            if (!Compare{}(*it, x)) total += *++it - x;
            s.erase(it2);
        } 
    }
};