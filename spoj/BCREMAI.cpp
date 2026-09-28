#include <bits/stdc++.h>
using namespace std;
typedef long long int64;

// ----------------- tiện ích số học -----------------
int64 egcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    int64 x1, y1;
    int64 g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int64 modinv(int64 a, int64 m) {
    int64 x, y;
    int64 g = egcd(a, m, x, y);
    if (g != 1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

// nhân modulo an toàn cho C++14
int64 mul_mod(int64 a, int64 b, int64 mod) {
    int64 res = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1) {
            res += a;
            if (res >= mod) res -= mod;
        }
        a <<= 1;
        if (a >= mod) a -= mod;
        b >>= 1;
    }
    return res;
}

int64 pow_mod(int64 a, int64 e, int64 mod) {
    if (mod == 1) return 0;
    int64 r = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}

// ----------------- phân tích thừa số -----------------
vector<pair<int,int>> factorize(int n) {
    vector<pair<int,int>> res;
    int t = n;
    for (int p = 2; p * p <= t; ++p) {
        if (t % p == 0) {
            int c = 0;
            while (t % p == 0) { t /= p; ++c; }
            res.push_back(make_pair(p, c));
        }
    }
    if (t > 1) res.push_back(make_pair(t, 1));
    return res;
}

// ----------------- Carmichael lambda -----------------
int64 lcm_int64(int64 a, int64 b) {
    return a / __gcd(a, b) * b;
}

int64 carmichael_of_prime_power(int p, int k) {
    if (p == 2) {
        if (k == 1) return 1;
        if (k == 2) return 2;
        return 1LL << (k - 2);
    } else {
        int64 pk1 = 1;
        for (int i = 0; i < k - 1; ++i) pk1 *= p;
        return pk1 * (p - 1);
    }
}

int64 carmichael(int n) {
    vector<pair<int,int>> fac = factorize(n);
    int64 L = 1;
    for (size_t i = 0; i < fac.size(); i++) {
        int p = fac[i].first, k = fac[i].second;
        int64 part = carmichael_of_prime_power(p, k);
        L = lcm_int64(L, part);
    }
    return L;
}

// ----------------- factorial with cap -----------------
pair<int64,bool> factorial_with_cap(int64 ai, int64 cap) {
    if (cap == 1) return make_pair(0, true);
    if (ai <= 0) return make_pair(1 % cap, false);
    if (ai >= cap) return make_pair(0, true); // factorial >= cap chắc chắn

    int64 prod = 1;
    bool ge = false;
    for (int64 x = 1; x <= ai; ++x) {
        prod *= x;
        if (prod >= cap) {
            ge = true;
            prod %= cap;
        }
    }
    return make_pair(prod % cap, ge);
}

// ----------------- memo recursion -----------------
map<pair<int,int>, pair<int64,bool>> memo; 

pair<int64,bool> tower_mod_with_cap(int idx, int n, const vector<int64> &a, int cap) {
    pair<int,int> key = make_pair(idx, cap);
    if (memo.count(key)) return memo[key];
    pair<int64,bool> res;
    if (cap == 1) {
        res = make_pair(0, true);
        return memo[key] = res;
    }
    if (idx == n-1) {
        res = factorial_with_cap(a[idx], cap);
        return memo[key] = res;
    }
    int64 lam = carmichael(cap);
    pair<int64,bool> exp_pair = tower_mod_with_cap(idx+1, n, a, (int)lam);
    int64 exp_mod = exp_pair.first;
    bool exp_ge = exp_pair.second;
    int64 exponent_used = exp_mod + (exp_ge ? lam : 0);

    pair<int64,bool> base_pair = factorial_with_cap(a[idx], cap);
    int64 base_mod = base_pair.first;
    int64 val = pow_mod(base_mod, exponent_used, cap);

    // check "is_ge"
    bool full_ge;
    if (base_pair.second) {
        full_ge = (exponent_used > 0);
    } else {
        int64 base_actual = base_mod;
        if (exponent_used == 0) {
            full_ge = (1 >= cap);
        } else {
            long long cur = 1;
            bool exceeded = false;
            for (int64 t = 0; t < min<int64>(exponent_used, (int64)1000); ++t) {
                cur *= base_actual;
                if (cur >= cap) { exceeded = true; break; }
            }
            if (exponent_used > 1000 && base_actual > 1) exceeded = true;
            full_ge = exceeded;
        }
    }
    res = make_pair(val % cap, full_ge);
    return memo[key] = res;
}

// ----------------- CRT -----------------
pair<int64,int64> crt_pair(int64 a1, int64 m1, int64 a2, int64 m2) {
    int64 x, y;
    int64 g = egcd(m1, m2, x, y);
    if ((a2 - a1) % g != 0) return make_pair(0, -1);
    int64 mod = m1 / g * m2;
    int64 mul = ((a2 - a1) / g) % (m2 / g);
    if (mul < 0) mul += (m2 / g);
    int64 t = (x * mul) % (m2 / g);
    if (t < 0) t += (m2 / g);
    int64 res = (a1 + m1 * t) % mod;
    if (res < 0) res += mod;
    return make_pair(res, mod);
}

// ----------------- main -----------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int64> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        if (m == 1) {
            cout << 0 << "\n";
            continue;
        }
        vector<pair<int,int>> fac = factorize(m);
        vector<pair<int64,int64>> rem_mods;
        memo.clear();
        for (size_t i = 0; i < fac.size(); i++) {
            int p = fac[i].first, k = fac[i].second;
            int64 mod_pk = 1;
            for (int j = 0; j < k; ++j) mod_pk *= p;
            pair<int64,bool> ans = tower_mod_with_cap(0, n, a, (int)mod_pk);
            rem_mods.push_back(make_pair(ans.first % mod_pk, mod_pk));
        }
        int64 cur_r = rem_mods[0].first;
        int64 cur_m = rem_mods[0].second;
        for (size_t i = 1; i < rem_mods.size(); ++i) {
            pair<int64,int64> pr = crt_pair(cur_r, cur_m, rem_mods[i].first, rem_mods[i].second);
            cur_r = pr.first;
            cur_m = pr.second;
        }
        cout << (cur_r % m + m) % m << "\n";
    }
    return 0;
}
