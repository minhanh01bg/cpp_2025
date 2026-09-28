#include <bits/stdc++.h>
using namespace std;

long long dp[105][105][2];
// dp[i][j][b] = số xâu nhị phân độ dài i
//               có đúng j cặp "11" liên tiếp (tức tổng bằng k)
//               và bit cuối cùng = b (0 hoặc 1)

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int test_id, n, k;
    cin >> test_id >> n >> k;

    memset(dp, 0, sizeof(dp));

    // Khởi tạo cho xâu độ dài 1:
    // chỉ có thể là "0" hoặc "1", và đều chưa tạo ra cặp "11"
    dp[1][0][0] = 1; // xâu "0"
    dp[1][0][1] = 1; // xâu "1"

    // Duyệt từng độ dài từ 1 -> n-1 để xây tiếp
    for (int i = 1; i < n; i++) {
      for (int j = 0; j <= k; j++) {
        // TH1: thêm bit 0 ở cuối
        // - nếu trước là 0 => không tăng số cặp "11"
        dp[i+1][j][0] += dp[i][j][0];
        // - nếu trước là 1 => cũng không tạo "11"
        dp[i+1][j][0] += dp[i][j][1];

        // TH2: thêm bit 1 ở cuối
        // - nếu trước là 0 => không tăng số cặp "11"
        dp[i+1][j][1] += dp[i][j][0];
        // - nếu trước là 1 => tạo thêm một cặp "11"
        if (j+1 <= k) {
          dp[i+1][j+1][1] += dp[i][j][1];
        }
      }
    }

    // Kết quả = tổng số xâu độ dài n có đúng k cặp "11",
    // bất kể bit cuối là 0 hay 1
    long long result = dp[n][k][0] + dp[n][k][1];
    cout << test_id << " " << result << "\n";
  }
  return 0;
}
