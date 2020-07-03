#include "2018_big_data.h"


void solve_1()
{
	while (1) {
		int n, num_get = 1, cur_prime = 2, cur_num = 3;
		cin >> n;
		while (num_get < n) {
			bool is_prime = true;
			int lim = sqrt(cur_num);
			for (int i = 3; i <= lim; i += 2) {
				if (cur_num % i == 0) {
					is_prime = false;
					break;
				}
			}
			if (is_prime) {
				cur_prime = cur_num;
				++num_get;
			}
			cur_num += 2;
		}
		cout << cur_prime << endl;
	}
}

void solve_2()
{
	string src, dst, now;
	cin >> src >> dst >> now;
	int mapping[26] = {}, rev_mapping[26] = {};
	int num_map = 0;
	bool success = true;
	for (int i = 0; i < 26; ++i) {
		mapping[i] = -1;
		rev_mapping[i] = -1;
	}
	
	for (int i = 0; i < src.length(); ++i) {
		int cur_src = src[i] - 'A';
		int cur_dst = dst[i] - 'A';
		if (mapping[cur_src] == -1 && rev_mapping[cur_dst] == -1) {
			mapping[cur_src] = cur_dst;
			rev_mapping[cur_dst] = cur_src;
			++num_map;
		}
		else if (mapping[cur_src] != -1 && rev_mapping[cur_dst] != -1) {
			if (mapping[cur_src] != cur_dst || rev_mapping[cur_dst] != cur_src) {
				success = false;
				break;
			}
		}
		else {
			success = false;
			break;
		}
	}
	if (!success || num_map!=26) {
		cout << "Failed";
	}
	else {
		for (int i = 0; i < now.length(); ++i) {
			cout << char('A' + mapping[now[i]-'A']);
		}
	}

}

int max_dist[10010][510][2] = {0};
void solve_4()
{
	ios::sync_with_stdio(false);
	int n, m;
	int dist[10010] = {};
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> dist[i];
	}
	max_dist[0][0][0] = 0;
	max_dist[0][1][1] = dist[0];
	for (int i = 1; i < n; ++i) {
		max_dist[i][1][1] = max_dist[i - 1][0][0] + dist[i];
		for (int j = 2; j <= m; ++j) {
			max_dist[i][j][1] = max_dist[i - 1][j - 1][1] + dist[i];
		}
		for (int j = 0; j < m; ++j) {
			max_dist[i][j][0] = 
				max(max_dist[i-1][j+1][0], max_dist[i-1][j+1][1]);
		}
		max_dist[i][0][0] = max(max_dist[i][0][0], max_dist[i - 1][0][0]);
	}
	cout << max(max_dist[n - 1][0][0], max_dist[n - 1][0][1]);
}


void solve_7()
{
	int n;
	while (1) {
		cin >> n;
		if (!n)
			break;
		while (1) {
			int tmp;
			cin >> tmp;
			if (!tmp)
				break;
			stack<int> stk;
			int cur_next = 1;
			bool success = true;

			while (cur_next < tmp) {
				stk.push(cur_next++);
			}
			++cur_next;
			for (int i = 1; i < n; ++i) {
				cin >> tmp;
				if (!success)
					continue;
				if (stk.empty() || stk.top() < tmp) {
					while (cur_next < tmp) {
						stk.push(cur_next++);
					}
					++cur_next;
				}
				else if (stk.top() == tmp)
					stk.pop();
				else {
					success = false;
				}
			}
			cout << ((success == true) ? "Yes" : "No") << endl;
		}
		cout << endl;
	}
}

inline bool char_to_bool(char ch)
{
	if (ch == ' ')
		return 0;
	if (ch == '|')
		return 1;
	if (ch == '_')
		return 1;
	assert(false);
}

const int digits[10][9] = {
	{0, 1, 0, 1, 0, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 1, 0, 0, 1},
	{0, 1, 0, 0, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 1, 1, 0, 1, 1},
	{0, 0, 0, 1, 1, 1, 0, 0, 1},
	{0, 1, 0, 1, 1, 0, 0, 1, 1},
	{0, 1, 0, 1, 1, 0, 1, 1, 1},
	{0, 1, 0, 0, 0, 1, 0, 0, 1},
	{0, 1, 0, 1, 1, 1, 1, 1, 1},
	{0, 1, 0, 1, 1, 1, 0, 1, 1}
};

void mark_avail(bool content[3][3], bool avail[10], int range)
{
	for (int i = 0; i < range; ++i) {
		bool cur_ok = true;
		for (int j = 0; j < 9; ++j) {
			int row = j / 3, col = j % 3;
			if (!content[row][col] || digits[i][j])
				continue;
			cur_ok = false;
			break;
		}
		if (cur_ok)
			avail[i] = 1;
		else
			avail[i] = 0;
	}
}

void solve_5()
{
	int num_cases;
	cin >> num_cases;
	char dummy[5] = {};
	cin.getline(dummy, 90);

	while (num_cases--) {
		char line[50] = {};
		bool content[2][4][3][3];
		bool avail[2][4][10] = { 0 };
		vector<int> valid_times[2][2];
		for (int i = 0; i < 3; ++i) {
			cin.getline(line, 50);
			for (int j = 0; j < 12; ++j) {
				int digit = j / 3;
				content[0][digit][i][j % 3] = char_to_bool(line[j]);
			}
			for (int k = 13, j = 0; k < 25; ++k, ++j) {
				int digit = j / 3;
				content[1][digit][i][j % 3] = char_to_bool(line[k]);
			}
		}

		for (int i = 0; i < 2; ++i) {
			mark_avail(content[i][0], avail[i][0], 3);
			mark_avail(content[i][1], avail[i][1], 10);
			mark_avail(content[i][2], avail[i][2], 6);
			mark_avail(content[i][3], avail[i][3], 10);
			// hours -> [i][0]
			for (int j = 0; j < 2; ++j) {
				if (avail[i][0][j]) {
					for (int k = 0; k < 10; ++k) {
						if (avail[i][1][k]) {
							int cur_hour = j * 10 + k;
							valid_times[i][0].push_back(cur_hour);
						}
					}
				}
			}
			if (avail[i][0][2]) {
				for (int k = 0; k < 4; ++k) {
					if (avail[i][1][k]) {
						int cur_hour = 20 + k;
						valid_times[i][0].push_back(cur_hour);
					}
				}
			}
			// minutes -> [i][1]
			for (int j = 0; j < 6; ++j) {
				if (avail[i][2][j]) {
					for (int k = 0; k < 10; ++k) {
						if (avail[i][3][k]) {
							int cur_min = j * 10 + k;
							valid_times[i][1].push_back(cur_min);
						}
					}
				}
			}
		}

		int ok_cases = 0, ok_hr, ok_mn;
		for (int i = 0; i < valid_times[0][0].size(); ++i) {
			for (int j = 0; j < valid_times[0][1].size(); ++j) {
				for (int k = 0; k < valid_times[1][0].size(); ++k) {
					for (int l = 0; l < valid_times[1][1].size(); ++l) {
						int hr1 = valid_times[0][0][i];
						int mn1 = valid_times[0][1][j];
						int hr2 = valid_times[1][0][k];
						int mn2 = valid_times[1][1][l];
						mn2 += 15;
						if (mn2 > 59) {
							mn2 = mn2 % 60;
							++hr2;
							if (hr2 > 23)
								hr2 = 0;
						}
						if (hr1 == hr2 && mn1 == mn2) {
							++ok_cases;
							ok_hr = hr1;
							ok_mn = mn1;
						}
					}
				}
			}
		}

		if (ok_cases == 1) {
			printf("%02d%02d\n", ok_hr, ok_mn);
		}
		else {
			cout << "Not Sure" << endl;
		}

	}
}

void solve_6()
{
	int is_greater[27][27] = {};
	char orders[27] = {};
	int n, m;
	while (1) {
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;
		memset(is_greater, 0, sizeof(is_greater));
		for (int i = 0; i < n; ++i) {
			is_greater[i][i] = -1;
		}
		string str;
		int stop_step = -1;
		bool incons = false, clear = false;
		for (int i = 0; i < m; ++i) {
			cin >> str;
			if (incons || clear)
				continue;

			memset(orders, 0, sizeof(orders));
			int small = str[0] - 'A';
			int big = str[2] - 'A';
			// cout << small << " " << big << endl;
			if (is_greater[big][small] == -1) {
				stop_step = i + 1;
				incons = true;
				continue;
			}
			is_greater[big][small] = 1;
			if (is_greater[small][big] == 1) {
				stop_step = i + 1;
				//assert(false);
				incons = true;
				continue;
			}
			is_greater[small][big] = -1;
			for (int bb = 0; bb < n; ++bb) {
				if (is_greater[bb][big] != 1) {
					continue;
				}
				if (is_greater[bb][small] == -1) {
					stop_step = i + 1;
					incons = true;
					break;
				}
				is_greater[bb][small] = 1;
				is_greater[small][bb] = -1;
				for (int ss = 0; ss < n; ++ss) {
					if (is_greater[small][ss] != 1) {
						continue;
					}
					if (is_greater[bb][ss] == -1) {
						stop_step = i + 1;
						incons = true;
						break;
					}
					is_greater[bb][ss] = 1;
					is_greater[ss][bb] = -1;
				}
			}
			for (int ss = 0; ss < n; ++ss) {
				if (is_greater[small][ss] != 1) {
					continue;
				}
				if (is_greater[big][ss] == -1) {
					stop_step = i + 1;
					incons = true;
					break;
				}
				is_greater[big][ss] = 1;
				is_greater[ss][big] = -1;
			}

			if (incons)
				continue;
			int ii;
			for (ii = 0; ii < n; ++ii) {
				int small_ct = 0;
				for (int j = 0; j < n; ++j)
					if (is_greater[ii][j]==1)
						++small_ct;
				if (orders[small_ct]) {	//!=0
					break;
				}
				orders[small_ct] = 'A' + ii;
			}
			if (ii == n) {
				clear = true;
				stop_step = i + 1;
			}	
		}

		if (incons) {
			cout << "Inconsistency found after " << stop_step << " relations." << endl;
		}
		else if (clear) {
			cout << "Sorted sequence determined after " << stop_step << " relations: ";
			for (int j = 0; j < n; ++j) {
				cout << orders[j];
			}
			cout << "." << endl;
		}
		else {
			cout << "Sorted sequence cannot be determined." << endl;
		}
	}
}


int points[24][2] = { {0,2},{0,4},{1,2},{1,4},{2,0},{2,1},{2,2},{2,3},{2,4},
					{2,5} ,{2,6},{3,2},{3,4} ,{4,0},{4,1},{4,2},{4,3},{4,4},
					{4,5} ,{4,6}, {5,2},{5,4},{6,2},{6,4} };

int board[7][7] = {};

struct node {
	string state;
	int step;
	string route;
	node(const string& st, int stp, const string& rt) :state(st), step(stp), route(rt) {}
};

struct avail_ret {
	bool avail;
	int symbol;
	avail_ret(bool av, int sy) :avail(av), symbol(sy) {}
};

avail_ret is_avail(const string& state)
{
	int symb = state[6] - '0';
	char cur = state[6];
	if (state[7] != cur || state[8] != cur || state[11] != cur || state[12] != cur ||
		state[15] != cur || state[16] != cur || state[17] != cur) {
		return avail_ret(false, -1);
	}
	return avail_ret(true, symb);
}

string permute(string init_state, int way)
{
	if (way == 1) {
		char tmp = init_state[0];
		init_state[0] = init_state[2];
		init_state[2] = init_state[6];
		init_state[6] = init_state[11];
		init_state[11] = init_state[15];
		init_state[15] = init_state[20];
		init_state[20] = init_state[22];
		init_state[22] = tmp;
		return init_state;
	}
	if (way == 2) {
		char tmp = init_state[1];
		init_state[1] = init_state[3];
		init_state[3] = init_state[8];
		init_state[8] = init_state[12];
		init_state[12] = init_state[17];
		init_state[17] = init_state[21];
		init_state[21] = init_state[23];
		init_state[23] = tmp;
		return init_state;
	}
	if (way == 3) {
		char tmp = init_state[10];
		init_state[10] = init_state[9];
		init_state[9] = init_state[8];
		init_state[8] = init_state[7];
		init_state[7] = init_state[6];
		init_state[6] = init_state[5];
		init_state[5] = init_state[4];
		init_state[4] = tmp;
		return init_state;
	}
	if (way == 4) {
		char tmp = init_state[19];
		init_state[19] = init_state[18];
		init_state[18] = init_state[17];
		init_state[17] = init_state[16];
		init_state[16] = init_state[15];
		init_state[15] = init_state[14];
		init_state[14] = init_state[13];
		init_state[13] = tmp;
		return init_state;
	}
	if (way == 5) {
		char tmp = init_state[23];
		init_state[23] = init_state[21];
		init_state[21] = init_state[17];
		init_state[17] = init_state[12];
		init_state[12] = init_state[8];
		init_state[8] = init_state[3];
		init_state[3] = init_state[1];
		init_state[1] = tmp;
		return init_state;
	}
	if (way == 6) {
		char tmp = init_state[22];
		init_state[22] = init_state[20];
		init_state[20] = init_state[15];
		init_state[15] = init_state[11];
		init_state[11] = init_state[6];
		init_state[6] = init_state[2];
		init_state[2] = init_state[0];
		init_state[0] = tmp;
		return init_state;
	}
	if (way == 7) {
		char tmp = init_state[13];
		init_state[13] = init_state[14];
		init_state[14] = init_state[15];
		init_state[15] = init_state[16];
		init_state[16] = init_state[17];
		init_state[17] = init_state[18];
		init_state[18] = init_state[19];
		init_state[19] = tmp;
		return init_state;
	}
	if (way == 8) {
		char tmp = init_state[4];
		init_state[4] = init_state[5];
		init_state[5] = init_state[6];
		init_state[6] = init_state[7];
		init_state[7] = init_state[8];
		init_state[8] = init_state[9];
		init_state[9] = init_state[10];
		init_state[10] = tmp;
		return init_state;
	}
	assert(false);
}

void solve_8()
{
	while (1) {
		int num;
		cin >> num;
		if (num == 0)
			break;
		char nums[25];
		nums[0] = '0' + num;
		for (int i = 1; i < 24; ++i) {
			cin >> num;
			nums[i] = char('0' + num);
		}
		nums[24] = '\0';
		string init = nums;
		avail_ret init_res = is_avail(init);
		if (init_res.avail) {
			cout << "No moves needed" << endl;
			cout << init_res.symbol << endl;
		}
		queue<node> que;
		set<string> visited;
		que.push(node(init, 0, string("")));
		bool stopped = false;
		while (!que.empty()) {
			node cur = que.front();
			que.pop();
			for (int cur_way = 1; cur_way <= 8; ++cur_way) {
				string new_state = permute(cur.state, cur_way);
				if (visited.find(new_state) != visited.end()) {
					continue;
				}
				char tmp[2] = "0";
				tmp[0] = 'A' + cur_way - 1;
				string new_route = cur.route + tmp;

				avail_ret res = is_avail(new_state);
				if (res.avail) {
					cout << new_route << endl << res.symbol << endl;
					stopped = true;
					break;
				}
				visited.insert(new_state);
				que.push(node(new_state, cur.step + 1, new_route));
			}
			if (stopped)
				break;
		}

	}
}