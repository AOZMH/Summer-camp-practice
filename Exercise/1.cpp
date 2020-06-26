#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int T, N;
int all_pts[10000][2];

int dist(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int SOLVE_1()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> N;
        int min_dist = 0x7fffffff;
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            all_pts[i][0] = x;
            all_pts[i][1] = y;
            for (int j = 0; j < i; ++j) {
                int tmp = dist(x, y, all_pts[j][0], all_pts[j][1]);
                if (tmp < min_dist) {
                    min_dist = tmp;
                }
            }
        }
        cout << min_dist << endl;
    }


    return 0;
}