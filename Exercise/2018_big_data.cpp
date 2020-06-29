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


void solve_8()
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