#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; 
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    vector<int> tail; // luôn tăng dần
    for (int x : a) {
      auto it = lower_bound(tail.begin(), tail.end(), x);
      if (it == tail.end()) tail.push_back(x);
      else *it = x;
    }
    cout << tail.size() << endl;
}