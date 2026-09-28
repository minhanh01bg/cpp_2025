#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// Cấu trúc lưu trữ trạng thái tại mỗi dung tích x
struct State {
    int closes = INF; // Số lần đóng thùng
    int y = -1;       // Dung tích còn lại của thùng kia

    // So sánh ưu tiên: số lần đóng thùng ít hơn > dung tích còn lại y lớn hơn
    bool is_better_than(const State& other) const {
        if (closes != other.closes) {
            return closes < other.closes;
        }
        return y > other.y;
    }
};

int main() {
    // Tối ưu hóa I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L, N;
    if (!(cin >> L >> N)) return 0;

    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // dp[x] chứa trạng thái khi thùng chứa sản phẩm hiện tại còn x dung tích
    vector<State> dp(L + 1);
    dp[L] = {0, L}; // Ban đầu có 2 thùng dung tích L

    for (int i = 0; i < N; ++i) {
        int val = a[i];
        vector<State> next_dp(L + 1);

        for (int x = 0; x <= L; ++x) {
            if (dp[x].closes == INF) continue;

            int c = dp[x].closes;
            int y = dp[x].y;

            // Lựa chọn 1: Đưa vào thùng hiện tại (dung tích x)
            if (x >= val) {
                State cand = {c, y};
                if (cand.is_better_than(next_dp[x - val])) {
                    next_dp[x - val] = cand;
                }
            }

            // Lựa chọn 2: Đưa vào thùng còn lại (dung tích y)
            if (y >= val) {
                State cand = {c, x};
                if (cand.is_better_than(next_dp[y - val])) {
                    next_dp[y - val] = cand;
                }
            }

            // Lựa chọn 3: Đóng thùng x, mở thùng mới chứa val
            {
                State cand = {c + 1, y};
                if (cand.is_better_than(next_dp[L - val])) {
                    next_dp[L - val] = cand;
                }
            }

            // Lựa chọn 4: Đóng thùng y, mở thùng mới chứa val
            {
                State cand = {c + 1, x};
                if (cand.is_better_than(next_dp[L - val])) {
                    next_dp[L - val] = cand;
                }
            }
        }
        dp = move(next_dp);
    }

    // Tìm số lần đóng thùng nhỏ nhất trong tất cả các trạng thái hợp lệ
    int min_closes = INF;
    for (int x = 0; x <= L; ++x) {
        if (dp[x].closes != INF) {
            min_closes = min(min_closes, dp[x].closes);
        }
    }

    // Kết quả = 2 thùng ban đầu + tổng số lần đóng thùng
    cout << min_closes + 2 << "\n";

    return 0;
}