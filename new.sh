#!/usr/bin/env bash
# newcp.sh [-f] <problem_name> — tạo file cpp template competitive programming
set -euo pipefail

force=0
if [[ "${1:-}" == "-f" ]]; then
    force=1
    shift
fi

if [[ $# -lt 1 ]]; then
    echo "Usage: newcp.sh [-f] <problem_name>" >&2
    exit 1
fi

name="$1"
name="${name%.cpp}"          # bỏ .cpp nếu gõ nhầm kèm sẵn
dir="$(dirname "$name")"
file="${name}.cpp"

if [[ "$dir" != "." ]]; then
    mkdir -p "$dir"
fi

if [[ -e "$file" && $force -eq 0 ]]; then
    echo "File $file đã tồn tại, dùng 'newcp.sh -f $name' để ghi đè." >&2
    exit 1
fi

cat > "$file" << 'EOF'
/*
 *     ___       __
 *    / (_)___  / /_
 *   / / / __ \/ __/
 *  / / / / / / /_
 * /_/_/_/ /_/\__/
 *
 *  Author : lint
 *  Created: __DATE_PLACEHOLDER__
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
EOF

echo "Tạo $file xong."
sed -i "s/__DATE_PLACEHOLDER__/$(date '+%Y-%m-%d %H:%M')/" "$file"