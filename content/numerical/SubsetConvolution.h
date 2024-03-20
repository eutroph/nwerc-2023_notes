/**
 * Author: Eu-Shaun Leong
 * Date: 2024-03-20
 * License: GNU Free Documentation License 1.2
 * Source: https://codeforces.com/blog/entry/72488
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{S \subseteq z} f[S] \cdot g[z \setminus S]$,
 * The size of $f,g$ must be a power of two.
 * Time: O(N (\log N)^2)
 * Status: stress-tested
 */
vi convSubset(vi f, vi g){
    int N = 31-__builtin_clz(sz(f));
    vector<vi>fhat(N+1,vi(1<<N,0)),ghat(N+1,vi(1<<N,0)),h(N+1,vi(1<<N,0));
    FOR(bm,0,(1<<N)-1){
        fhat[__builtin_popcount(bm)][bm] = f[bm];
        ghat[__builtin_popcount(bm)][bm] = g[bm];
    }
    FOR(i,0,N)FOR(j,0,N-1)FOR(bm,0,(1<<N)-1)if(bm&(1<<j)){
        fhat[i][bm] += fhat[i][bm^(1<<j)];
        ghat[i][bm] += ghat[i][bm^(1<<j)];
    }
    FOR(bm,0,(1<<N)-1)FOR(i,0,N)FOR(j,0,i)
        h[i][bm] += fhat[j][bm]*ghat[i-j][bm];
    FOR(i,0,N)FOR(j,0,N-1)FOR(bm,0,(1<<N)-1)if(bm&(1<<j))
        h[i][bm] -= h[i][bm^(1<<j)];
    vi fog(1<<N);
    FOR(bm,0,(1<<N)-1)fog[bm] = h[__builtin_popcount(bm)][bm];
    return fog;
}