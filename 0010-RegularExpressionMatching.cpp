#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define DEBUG

class Solution {
public:
	bool isMatch(string s, string p) {
		unsigned s_size = s.size();
		unsigned p_size = p.size();
		vector<vector<bool>> table;
		vector<bool> row;
		row.resize(s_size + 1, false);
		table.resize(p_size + 1, row);
		table[p_size][s_size] = true;	
		for (int i = p_size - 1; i >= 0; --i) {
			for (int j = s_size - 1; j >= 0; --j) {
				if (s[j] == p[i] || p[i] == '.') {
					table[i][j] = table[i][j] | table[i+1][j+1];
				} else if (p[i] == '*') {
					char prefix = p[i - 1];	
					bool any = (prefix == '.');
					if (any) {
						for (int k = j; k <= s_size; k++) {
							if (table[i + 1][k]) {
								table[i][j] = true;
								break;
							}
						}
					} else {
						for (int k = j; k <= s_size; k++) {
							if (table[i + 1][k]) {
								table[i][j] = true;
								break;
							}
							if (s[k] != prefix) {
								break;
							}
						}
					}
					for (int k = 0; k <= s_size; k++) {
						if (table[i+1][k]) {
							table[i][k] = true;
							table[i - 1][k] = true;
						}
					}
				}
				if (i + 1 < p_size && p[i+1] == '*') {
					table[i][j] = table[i][j] | table[i+1][j];
				}
			}
			if (p[i] == '*') {
				for (int k = 0; k <= s_size; k++) {
					if (table[i+1][k]) {
						table[i][k] = true;
						table[i - 1][k] = true;
					}
				}
			}
		}
#ifdef DEBUG
		cout << ' ' << ' ';
		for (int j = 0; j < s_size; j++) {
			cout << s[j] << ' ';
		}
		cout << endl;
		for (int i = 0; i <= p_size; i++) {
			if (i != p_size) cout << p[i] << " ";
			if (i == p_size) cout << ' ' << ' ';
			for (int j = 0; j <= s_size; j++) {
				cout << table[i][j] << " ";
			}
			cout << endl;
		}
#endif
		return table[0][0];
	};
};

struct testcase {
	string s;
	string p;
};

#define TESTCASES 6

struct testcase testcases[TESTCASES] = {
	{"", ".*"},
	{"mississippi", "mis*is*p*."},
	{"aa", "a*"},
	{"aaa", ".*"},
	{"aab", "c*a*b"},
	{"a", "ab*"},
};

int main() {
	Solution sol;
	for (int i = 0; i < TESTCASES; i++) {
		string s = testcases[i].s;
		string p = testcases[i].p;
		cout << "string = " << s << " pattern = " << p << endl;
		if (sol.isMatch(s, p)) {
			cout << "Match!" << endl;
		} else {
			cout << "Not match!" << endl;
		}
		cout << endl;
	}
	return 0;
}
