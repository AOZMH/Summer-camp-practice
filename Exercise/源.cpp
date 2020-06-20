#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <cstring>
#include <math.h>
using namespace std;


vector<string> split(const string& str, const string& delim) {
    vector<string> res;
    char* source = new char[str.length() + 1];
    strcpy(source, str.c_str());
    char* p = strtok(source, delim.c_str());
    while (p) {
        res.push_back(p);
        p = strtok(NULL, delim.c_str());
    }
    delete[] source;
    return res;
}

int T, N;


int main()
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