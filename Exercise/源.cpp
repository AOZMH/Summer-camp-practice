#define _CRT_SECURE_NO_WARNINGS
#include "2019_big_data.h"


/*vector<string> split(const string& str, const string& delim) {
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
}*/


int main()
{   
    //SOLVE_3();

    int N, K, lens[10005];
    cin >> N >> K;
    float tmp;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        lens[i] = tmp * 100;
    }
    int l_len = 0, r_len = 10000002;

    while ((l_len < r_len - 1)) {
        int mid = (l_len + r_len) / 2;
        if (mid == 0)
            break;
        int avail = 0;
        for (int i = 0; i < N; ++i) {
            avail += lens[i] / mid;
            if (avail >= K)
                break;
        }
        if (avail >= K) {
            l_len = mid;
            continue;
        }
        else {
            r_len = mid;
            continue;
        }
    }

    //printf("%.2f", float(l_len) / 100);
    cout.flags(ios::fixed);
    cout.precision(2);
    cout << float(l_len) / 100;

    return 0;
}