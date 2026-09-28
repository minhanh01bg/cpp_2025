#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int caseNo = 1;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<vector<int>> a(n, vector<int>(m));
        vector<int> heights;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                heights.push_back(a[i][j]);
            }

        // Dò từ f = 1 tới maxH (tăng dần mực nước) ->  Loại bỏ trùng và sắp xếp
        sort(heights.begin(), heights.end());
        heights.erase(unique(heights.begin(), heights.end()), heights.end());

        const int di[4] = {-1, 1, 0, 0};
        const int dj[4] = {0, 0, -1, 1};

        bool splitted = false;
        int answerF = -1;

        for (int h : heights) {
            if (h == 0) continue; // bỏ qua mực nước biển gốc
            // flooded[i][j] = true nếu ô đó bị nước biển ngập (có đường từ biên qua các ô <= f)
            vector<vector<char>> flooded(n, vector<char>(m, 0));
            queue<pair<int,int>> q;

            // Lan nước từ biên
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i == 0 || i == n-1 || j == 0 || j == m-1) {
                        if (a[i][j] <= h && !flooded[i][j]) {
                            flooded[i][j] = 1;
                            q.push({i,j});
                        }
                    }
                }
            }

            // Lan nước bằng BFS qua các ô có độ cao <= h
            while (!q.empty()) {
                auto [r,c] = q.front(); q.pop();
                for (int k = 0; k < 4; k++) {
                    int nr = r + di[k], nc = c + dj[k];
                    if (nr>=0 && nr<n && nc>=0 && nc<m && !flooded[nr][nc] && a[nr][nc] <= h) {
                        flooded[nr][nc] = 1;
                        q.push({nr,nc});
                    }
                }
            }

            // Đếm số thành phần đất, // Đếm số thành phần liên thông trong phần đất còn lại (không bị ngập)
            vector<vector<char>> seen(n, vector<char>(m, 0));
            int comps = 0;
            for (int i = 0; i < n && comps < 2; i++) {
                for (int j = 0; j < m && comps < 2; j++) {
                    if (!flooded[i][j] && !seen[i][j]) {
                        comps++;
                        queue<pair<int,int>> q2;
                        seen[i][j] = 1;
                        q2.push({i,j});
                        while (!q2.empty()) {
                            auto [r,c] = q2.front(); q2.pop();
                            for (int k = 0; k < 4; k++) {
                                int nr = r + di[k], nc = c + dj[k];
                                if (nr>=0 && nr<n && nc>=0 && nc<m && !flooded[nr][nc] && !seen[nr][nc]) {
                                    seen[nr][nc] = 1;
                                    q2.push({nr,nc});
                                }
                            }
                        }
                    }
                }
            }

            if (comps >= 2) {
                splitted = true;
                answerF = h;
                break;
            }
        }

        if (splitted) {
            cout << "Case " << caseNo << ": Island splits when ocean rises " << answerF << " feet.\n";
        } else {
            cout << "Case " << caseNo << ": Island never splits.\n";
        }
        caseNo++;
    }

    return 0;
}
