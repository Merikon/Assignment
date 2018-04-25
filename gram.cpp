#include <cstdio>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 50;
const int MAX_LENGTH = 5001;
const int Q_GRAM = 2;
const int HASH_BASE = 357;

vector <string> str;
string qstr;

char buf[MAX_LENGTH];

bool findSubstr(const string &str, const string sub) {
	unsigned hstr = 0, hsub = 0;
	if (str.length() < sub.length()) {
		return 0;
	}
	unsigned pw = 1;
	for (int i = 0; i < sub.length(); i++) {
		hstr = hstr * HASH_BASE + str[i];
		hsub = hsub * HASH_BASE + sub[i];
 		pw *= HASH_BASE;
	}
	for (int i = 0; i + sub.length() <= str.length(); i++) {
		if (hstr == hsub) {
			return 1;
		}
		hstr = hstr * HASH_BASE + str[sub.length() + i] - pw * str[i];
	}
	return 0;
}

int main() {
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	int n, m;
	scanf("%d%d\n", &n, &m);
	unordered_map <unsigned, vector <int>> invList;
	unordered_set <unsigned> grams;
	for (int i = 0; i < n; i++) {
		gets(buf);
		int len = strlen(buf);
		if (buf[len - 1] == '\n') {
			buf[len - 1] = 0;
		}
		str.push_back(buf);
		grams.clear();
		for (int j = 0; j + Q_GRAM <= str.back().length(); j++) {
			unsigned h = 0;
			for (int k = 0; k < Q_GRAM; k++) {
				h = h * HASH_BASE + str.back()[j + k];
			}
			grams.insert(h);
		}
		for (auto h : grams) {
			if (!invList.count(h)) {
				invList[h] = vector <int> (0);
				invList[h].push_back(i);
			}
			if (invList[h].back() != i) {
				invList[h].push_back(i);
			}
		}
	}
	vector <int> candidate;
	vector <int> filter;
	for (int i = 0; i < m; i++) {
		candidate.clear();
		for (int i = 0; i < n; i++) {
			candidate.push_back(i);
		}
		gets(buf);
		int len = strlen(buf);
		if (buf[len - 1] == '\n') {
			buf[len - 1] = 0;
		}
		qstr = string(buf);
		grams.clear();
		for (int j = 0; j + Q_GRAM <= qstr.length(); j++) {
			unsigned h = 0;
			for (int k = 0; k < Q_GRAM; k++) {
				h = h * HASH_BASE + qstr[j + k];
			}
			grams.insert(h);
		}
		int genc = 0;
		int gent = grams.size();
		for (auto h : grams) {
			if (candidate.size() == 1) break;
			filter.clear();
			if (candidate.size() < invList[h].size()) {
				for (int k = 0; k < candidate.size(); k++) {
					if (binary_search(invList[h].begin(), invList[h].end(), candidate[k])) {
						filter.push_back(candidate[k]);
					}
				}
			} else {
				for (int k = 0; k < invList[h].size(); k++) {
					if (binary_search(candidate.begin(), candidate.end(), invList[h][k])) {
						filter.push_back(invList[h][k]);
					}
				}
			}
			candidate.clear();
			for (const auto idx : filter) candidate.push_back(idx);
		}
		for (const auto &idx : candidate) {
			if (findSubstr(str[idx], qstr)) {
				printf("%d ", idx + 1);
			}
		}
		printf("\n");
	}
}
