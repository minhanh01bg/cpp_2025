#include<bits/stdc++.h>
using namespace std;

// Hàm tính số nguyên tố từ 1 đến n và lưu vào vector
vector<int> sieve(int n) {
    vector<bool> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i*i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i*i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++) if (isPrime[i]) primes.push_back(i);
    return primes;
}
int main() {
  int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    // tìm các số nguyên tố nhỏ hơn n
    vector<int> primes = sieve(n);
    int l = 0, r = 0; // cộng dần lên, khi nào lớn hơn n thì trừ dần từ đầu đi
    long long sum = 0, count = 0;
 
    while(true){
      if (sum >= n){
        if (sum == n) count ++;
        sum -= primes[l++];
      } else {
        if (r == (int)primes.size()) break;
        sum += primes[r++];
      }
    }
    cout << count << '\n';
  }
}