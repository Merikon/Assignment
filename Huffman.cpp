#include <cstdio>
#include <queue>

using namespace std;

long long getans(priority_queue <int> &p) {
    long long sum = 0;
    int a, b;
    while (true) {
        a = ~p.top();
        p.pop();
        if (p.empty()) return sum;
        b = ~p.top();
        p.pop();
        sum += a + b;
        p.push(~(a + b));
    }
}

int main() {
    int n, x;
    scanf("%d", &n);

    priority_queue <int> p;

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        p.push(~x);
    }
    printf("%lld\n", getans(p));
    char st[10];
    scanf("%s", st);
    return 0;
} 
