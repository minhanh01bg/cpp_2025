/*
 *     ___       __
 *    / (_)___  / /_
 *   / / / __ \/ __/
 *  / / / / / / /_
 * /_/_/_/ /_/\__/
 *
 *  Author : lint
 *  Created: 2026-07-27 16:41
 */
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define vll vector<ll>
#define vpii vector<pii>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define FORD(i,a,b) for (int i = (a); i >= (b); --i)
#define endl '\n'

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<class T> bool ckmin(T& a, const T& b) { return b < a ? (a = b, true) : false; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? (a = b, true) : false; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
template<class T> ostream& operator<<(ostream& os, const vector<T>& v){
    os << "["; for (size_t i = 0; i < v.size(); ++i) os << v[i] << (i+1<v.size()?", ":""); return os << "]";
}
template<class A, class B> ostream& operator<<(ostream& os, const pair<A,B>& p){
    return os << "(" << p.first << ", " << p.second << ")";
}
#define debug(x) cerr << "[" << #x << "] = " << (x) << endl
#else
#define debug(x)
#endif

void solve() {
  int n;
  cin>>n;
  vector<int>dp(3);
  cin >> dp[0] >> dp[1] >> dp[2];
  for (int i = 1; i < n; i++){
    int a,b,c;
    cin >> a >> b >> c;

    // Tính điểm tối ưu mới cho ngày thứ i dựa trên ngày i - 1
    int new_dpa = a + max(dp[1],dp[2]);
    int new_dpb = b + max(dp[0], dp[2]);
    int new_dpc = c + max(dp[0], dp[1]);

    // update
    dp[0] = new_dpa;
    dp[1] = new_dpb;
    dp[2] = new_dpc;
  }
  cout << max({dp[0], dp[1], dp[2]}) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifdef LOCAL
    if (!freopen("input.txt", "r", stdin)) {};
#endif

    int tc = 1;
    // cin >> tc;
    while (tc--) solve();

    return 0;
}
