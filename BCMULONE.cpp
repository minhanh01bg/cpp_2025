/**
                                        .-''-.
                                      .' .-.  )
                                     / .'  / /
    .-''` ''-.        .-''` ''-.    (_/   / /
  .'          '.    .'          '.       / /
 /              `  /              `     / /
'                ''                '   . '
|         .-.    ||         .-.    |  / /    _.-')
.        |   |   ..        |   |   ..' '  _.'.-''
 .       '._.'  /  .       '._.'  //  /.-'_.'
  '._         .'    '._         .'/    _.'
     '-....-'`         '-....-'` ( _.-'
 */
#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
using ldb = long double;
using db = double;
using str = string; // yay python!

using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<db>;
using vs = vector<str>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;

// pairs
#define mp make_pair
// #define fi first
#define se second

// vectors
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pf push_front
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound

#define null NULL
#define endl '\n'
// loops
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
// #define rep(i, a) rep(i, 0, a)
#define rof(i, a, b) for (int i = (b); i >= (a); --i)
#define r0f(i, a) rof(i, 0, a)
#define rtf(t) for (int _ = 1; _ <= (t); ++_)
#define trav(a, x) for (auto &a : x)
#define reset(x) memset(x, 0, sizeof(x))
const int mod = 1e9 + 7;
const int MX = 5e4 + 7;
const ll INF = 1e18;
const int NM = 1e6 + 7;
const ldb PI = acos((ldb)-1);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}; // for every grid problem!!
/*_______________________________________MY CODE_____________________________________*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    if (!(cin >> k)) return 0;
    while (k--) {
        int n;
        cin >> n;

        // Tạo dãy hệ số tam giác trước khi carry: length = 2n-1
        const int L = 2 * n - 1;
        vector<int> a(L);
        // Tăng dần: 1..n
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        // Giảm dần: n-1..1
        for (int i = n; i < L; ++i) a[i] = 2 * n - 1 - i;

        // Thực hiện carry từ phải sang trái
        long long carry = 0;
        for (int i = L - 1; i >= 0; --i) {
            long long v = a[i] + carry;
            a[i] = int(v % 10);
            carry = v / 10;
        }

        // Xuất phần carry còn lại (nếu có)
        string out;
        if (carry > 0) {
            string head;
            while (carry > 0) {
                head.push_back(char('0' + (carry % 10)));
                carry /= 10;
            }
            reverse(head.begin(), head.end());
            out.reserve(head.size() + L);
            out += head;
        } else {
            out.reserve(L);
        }

        // Xuất các chữ số sau khi mod 10
        for (int d : a) out.push_back(char('0' + d));
        cout << out << '\n';
    }
    return 0;
}
