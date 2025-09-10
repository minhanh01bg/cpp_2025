/**
 * Yêu cầu:
Có N học sinh, M dạng thi, giới hạn K học sinh tối đa được gửi đi.

Một học sinh chỉ được tham dự tối đa 1 dạng thi.

Nhưng một dạng thi có thể nhận nhiều học sinh (điều này được khẳng định nhờ test 2, nếu không thì kết quả 15.0 là bất khả thi).

Mục tiêu: chọn ≤ K học sinh và gán họ vào một dạng thi sao cho tổng kiến thức tối đa.

Test 2.
Input:
4 4 3
4 5.0 2 4.0 3 2.0 1 1.0
2 2.0 3 1.0 1 0.5 4 0.3
4 6.0 3 5.0 2 2.0 1 0.0
1 4.0 2 3.0 4 0.6 3 0.3


Output:
15.0

 * Nhận xét quan trọng

Mỗi học sinh j có nhiều điểm số: score[i][j] với từng dạng i.

Nếu ta quyết định gửi học sinh j đi thi, thì chỉ cần chọn dạng thi mà học sinh đó giỏi nhất (điểm max).

Lý do:

Vì mỗi học sinh chỉ được chọn một lần.

Không bị hạn chế số học sinh trên một dạng thi.

Do đó chọn điểm cao nhất của học sinh đó luôn là tối ưu.

 * Cách giải

Với mỗi học sinh j (1..N), tính best[j] = max(score[i][j]) trên tất cả i (dạng thi).
→ best[j] là "giá trị kiến thức tốt nhất có thể đóng góp" nếu chọn học sinh này.

Gom tất cả best[j] thành 1 danh sách.

Sắp xếp giảm dần.

Chọn ra K giá trị lớn nhất (nếu K > N thì chỉ lấy N).

Tổng các giá trị đó chính là kết quả.

=> tìm điểm cao nhất của các học sinh, đưa vào mảng, sau đó sắp xếp lại rồi lấy tổng k đầu tiên (thỏa mãn học sinh thỉ tham gia một dạng thi)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;

    // score[i][j]: i = 1..M (task), j = 1..N (student), scaled by 10
    vector<vector<int>> score(M+1, vector<int>(N+1, 0));
    for (int i = 1; i <= M; ++i) {
        for (int cnt = 0; cnt < N; ++cnt) {
            int idx; double s;
            cin >> idx >> s;
            score[i][idx] = (int)round(s * 10.0);
        }
    }

    // best per student
    vector<int> best(N+1, 0);
    for (int j = 1; j <= N; ++j) {
        int mx = 0;
        for (int i = 1; i <= M; ++i) mx = max(mx, score[i][j]);
        best[j] = mx;
    }

    // collect and sort descending
    vector<int> vals;
    for (int j = 1; j <= N; ++j) vals.push_back(best[j]);
    sort(vals.rbegin(), vals.rend());

    int take = min(K, N);
    long long sum = 0;
    for (int i = 0; i < take; ++i) sum += vals[i];

    double ans = sum / 10.0;
    cout.setf(std::ios::fixed);
    cout << setprecision(1) << ans << "\n";
    return 0;
}
