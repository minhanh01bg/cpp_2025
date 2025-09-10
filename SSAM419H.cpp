#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y, dir, turns;
};

int dx[4] = {-1, 1, 0, 0}; // U, D, L, R
int dy[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) cin >> grid[i];

        int sx, sy, tx, ty;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'S') { sx = i; sy = j; }
                if (grid[i][j] == 'T') { tx = i; ty = j; }
            }

        // visited[x][y][dir][turns]
        static bool visited[501][501][4][3];
        memset(visited, 0, sizeof(visited));

        queue<State> q;
        for (int d = 0; d < 4; d++) {
            visited[sx][sy][d][0] = true;
            q.push({sx, sy, d, 0});
        }

        bool ok = false;
        while (!q.empty() && !ok) {
            auto [x, y, dir, turns] = q.front();
            q.pop();
            if (x == tx && y == ty) { ok = true; break; }

            for (int nd = 0; nd < 4; nd++) {
                int nx = x + dx[nd], ny = y + dy[nd];
                int nt = turns + (nd != dir);
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if (grid[nx][ny] == '*') continue;
                if (nt > 2) continue;
                if (!visited[nx][ny][nd][nt]) {
                    visited[nx][ny][nd][nt] = true;
                    q.push({nx, ny, nd, nt});
                }
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }
}
