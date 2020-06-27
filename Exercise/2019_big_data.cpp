#include "2019_big_data.h"

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

struct patient {
    string no;
    int age, order;
    patient() {}
    patient(string &n, int &a, int &o):no(n),age(a),order(o) {}
    bool operator < (const patient& obj) const {
        if (age >= 60) {
            if (obj.age < 60)
                return true;
            if (age == obj.age)
                return order < obj.order;
            return age > obj.age;
        }
        if (obj.age >= 60)
            return false;
        return order < obj.order;
    }
};

patient info[101];

int SOLVE_2()
{
    ios::sync_with_stdio(false);
    cin >> N;
    string no;
    int age;
    for (int i = 0; i < N; ++i) {
        cin >> no >> age;
        info[i] = patient(no, age, i);
    }
    sort(info, info+N);
    for (int i = 0; i < N; ++i) {
        cout << info[i].no << endl;
    }
    return 0;
}

int SOLVE_5()
{
    ios::sync_with_stdio(false);
    int p[101], n[101];
    int max_inc[101][2];
    cin >> T >> N;
    for (int i = 0; i < T; ++i) {
        cin >> p[i] >> n[i];
    }
    max_inc[0][0] = p[0];
    max_inc[0][1] = n[0
    ];
    for (int i = 1; i < T; ++i) {
        max_inc[i][0] = max(max_inc[i - 1][0] + p[i], max_inc[i - 1][1] + p[i] - N);
        max_inc[i][1] = max(max_inc[i - 1][1] + n[i], max_inc[i - 1][0] + n[i] - N);
    }

    cout << max(max_inc[T - 1][0], max_inc[T - 1][1]);
    return 0;
}

int board[10][10] = {};
bool col_avail[10] = {};
int cal_num(int row, int num)
{
    if (num == 0)
        return 1;
    if ((N - row) < num)
        return 0;
    int cur_res = 0;
    for (int i = 0; i < N; ++i) {
        if (board[row][i] == 1 && col_avail[i]) {
            board[row][i] = 2;
            col_avail[i] = false;
            cur_res += cal_num(row + 1, num - 1);
            board[row][i] = 1;
            col_avail[i] = true;
        }
    }
    cur_res += cal_num(row + 1, num);
    return cur_res;
}

int SOLVE_4()
{
    ios::sync_with_stdio(false);
    int k;
    char tmp;
    while (1) {
        for (int i = 0; i < 10; ++i)
            col_avail[i] = true;
        memset(board, 0, sizeof(board));
        cin >> N >> k;
        if (N == -1 && k == -1)
            break;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                cin >> tmp;
                if (tmp == '#')
                    board[i][j] = 1;
                else
                    board[i][j] = 0;
            }
        cout << cal_num(0, k) << endl;
    }
    return 0;
}

inline bool in_array(int cr, int cc, int r, int c, int arr[25][25])
{
    if (arr[cr][cc]!=-1 || cr < 0 || cc < 0 || cr >= r || cc >= c)
        return false;
    return true;
}

int SOLVE_6()
{
    ios::sync_with_stdio(false);
    int dirs[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
    int arr[25][25] = {};
    int R, C;
    char tmp[200] = {}, *str;
    cin >> R >> C;
    cin.getline(tmp, 200);
    str = tmp + 1;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            arr[i][j] = -1;
        }
    }
    int str_len = strlen(str);
    int cur_dir = 0, cur_r = 0, cur_c = 0;
    int nxt_r, nxt_c;
    for (int i = 0; i < str_len; ++i) {
        char cur = str[i];
        if (cur == ' ') {
            for (int j = 0; j < 5; ++j) {
                arr[cur_r][cur_c] = 0;
                nxt_r = cur_r + dirs[cur_dir][0];
                nxt_c = cur_c + dirs[cur_dir][1];
                if (in_array(nxt_r, nxt_c, R, C, arr)) {
                    cur_r = nxt_r;
                    cur_c = nxt_c;
                }
                else {
                    cur_dir = (cur_dir + 1) % 4;
                    cur_r = cur_r + dirs[cur_dir][0];
                    cur_c = cur_c + dirs[cur_dir][1];
                }
            }
        }
        else {
            int cur_num = cur - 'A' + 1;
            for (int j = 0; j < 5; ++j) {
                int cur_feed = ((cur_num & (1 << (4 - j))) != 0);
                arr[cur_r][cur_c] = cur_feed;
                nxt_r = cur_r + dirs[cur_dir][0];
                nxt_c = cur_c + dirs[cur_dir][1];
                if (in_array(nxt_r, nxt_c, R, C, arr)){
                    cur_r = nxt_r;
                    cur_c = nxt_c;
                }
                else {
                    cur_dir = (cur_dir + 1) % 4;
                    cur_r = cur_r + dirs[cur_dir][0];
                    cur_c = cur_c + dirs[cur_dir][1];
                }
            }
        }
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (arr[i][j] != 0 && arr[i][j] != 1)
                cout << 0;
            else
                cout << arr[i][j];
        }
    }
    return 0;
}

struct state {
    string str;
    int step;
    state(const string &s, const int &stp):str(s),step(stp) {}
};

int SOLVE_7()
{
    queue<state> que;
    string st, ed, tmp;
    map<string, bool> dict;
    cin >> st >> ed;
    while (cin >> tmp) {
        dict[tmp] = true;
    }
    
    que.push(state(st, 1));
    while(!que.empty()){
        state cur_state = que.front();
        que.pop();
        // if can convert to answer
        int match_len = 0;
        for (int i = 0; i < cur_state.str.length(); ++i) {
            if (cur_state.str[i] == ed[i])
                ++match_len;
        }
        if (match_len == cur_state.str.length() - 1) {
            // got answer!
            cout << cur_state.step + 1;
            return 0;
        }

        map<string, bool>::iterator ptr;
        for (ptr = dict.begin(); ptr != dict.end(); ++ptr) {
            // judge duplicity
            if (!ptr->second)
                continue;
            // judge if can convert
            int match_len = 0;
            for (int i = 0; i < cur_state.str.length(); ++i) {
                if (cur_state.str[i] == ptr->first[i]) {
                    ++match_len;
                }
            }
            if (match_len != cur_state.str.length() - 1)
                continue;
            // can convert
            ptr->second = false;
            que.push(state(ptr->first, cur_state.step + 1));
        }
    }
    cout << 0;

    return 0;
}


int SOLVE_3()
{
    int N, K, lens[10005];
    cin >> N >> K;
    float tmp;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        lens[i] = tmp * 100;
    }
    int l_len = 0, r_len = 10000002;

    while ((l_len < r_len-1)) {
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