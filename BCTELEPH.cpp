#include <bits/stdc++.h>
using namespace std;

// Hàm kiểm tra xem str1 có phải là tiền tố của str2 hay không
bool isPrefix(const string& str1, const string& str2) {
    if (str1.length() > str2.length()) return false;
    for (size_t i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) return false;
    }
    return true;
}

// Hàm kiểm tra tính nhất quán của danh sách số điện thoại
bool isConsistent(vector<string>& phones, int n) {
    // Sắp xếp danh sách số điện thoại theo thứ tự từ điển
    sort(phones.begin(), phones.end());
    
    // Kiểm tra các cặp số liền kề
    for (int i = 0; i < n - 1; i++) {
        if (isPrefix(phones[i], phones[i + 1])) {
            return false; // Không nhất quán nếu có số là tiền tố của số khác
        }
    }
    return true; // Nhất quán nếu không tìm thấy tiền tố
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t; // Số lượng bộ test
    while (t--) {
        int n;
        cin >> n; // Số lượng số điện thoại
        vector<string> phones(n);
        
        // Đọc danh sách số điện thoại
        for (int i = 0; i < n; i++) {
            cin >> phones[i];
        }
        
        // Kiểm tra và in kết quả
        if (isConsistent(phones, n)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}