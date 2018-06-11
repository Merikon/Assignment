#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class node {
public:
	int idx, f, t;
	string name, s, b;
	node (string name, int idx, char gender) {
		this->name = name;
		this->idx = idx;
		s = gender;
		t = 0;
		b = "";
	}
};

int main() {
	int n, m;
	char a[100], b[100], c[100];
	unordered_map <string, int> mp;
	vector <node> nodes;
	nodes.push_back(node("root", 0, 'M'));
	mp["root"] = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s%s%s", a, b, c);
		if (!mp.count(b)) {
			mp[b] = nodes.size();
			nodes.push_back(node(b, nodes.size(), c[0]));
		}
		int x = mp[a], y = mp[b];
		nodes[x].s += nodes[y].s[0];
		nodes[y].f = x;
	}
	for (int i = nodes.size() - 1; i; i--) {
		auto &node = nodes[i];
		node.b = string("(") + node.s[0] + node.b + ")";
//		printf("%s\n", node.b);
		nodes[node.f].b += node.b;
	}
	nodes[0].b = string("(") + nodes[0].s[0] + nodes[0].b + ")";
//	for (const auto &node : nodes) {
//		printf("%s %s %s\n", node.name.c_str(), node.s.c_str(), node.b.c_str());
//	}
	unordered_map <string, int> hash1, hash2;
	for (const auto &node : nodes) {
		if (!hash1.count(node.s)) {
			hash1[node.s] = 0;
		}
		if (!hash2.count(node.b)) {
			hash2[node.b] = 0;
		}
		hash1[node.s]++;
		hash2[node.b]++;
	}
	for (int i = 0; i < m; i++) {
		scanf("%s%s", &a, &b);
		if (a[0] == 'F') {
			const auto &node = nodes[mp[b]];
			printf("%d\n", hash1[node.s] - 1);
		}
		if (a[0] == 'S') {
			const auto &node = nodes[mp[b]];
			printf("%d\n", hash2[node.b] - 1);
		}
	}
}
