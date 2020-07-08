#include <bits/stdc++.h>
using namespace std;
const int N = 128, M = 200;

int head[N], to[M], nxt[M], degree[N], ne = 0;
void add_edge(int f, int t) {
	to[ne] = t;
	nxt[ne] = head[f];
	degree[t]++;
	head[f] = ne++;
}
#define neigh(u,e,v) for(int e = head[u], v; v = to[e], ~e; e = nxt[e])
#define inoutfile freopen("input.txt", "rt", stdin);freopen("output.txt", "wt", stdout)

char nodes[N], nl;
int n = 0;
bool visit[N];
char order[10000];
int c = 0;
vector<char> res;
vector<char*> allres;

void TOPO()
{
	bool flag = 0;
	for (int j = 0; j < n; j++)
	{
		int u = nodes[j];
		if (visit[u] || degree[u]) continue;
		
		visit[u] = 1;
		res.push_back(u);
		neigh(u, e, v)
			degree[v]--;

		TOPO();

		visit[u] = 0;
		res.pop_back();
		neigh(u, e, v)
			degree[v]++;

		flag = 1;
	}

	if (!flag){
		char *x = new char[n+1];
		copy(res.begin(), res.end(), x);
		x[n] = '\0';
		allres.push_back(x);
		
	}
}


void init() {
	n = 0;
	memset(head, -1, sizeof head);
	memset(degree, 0, sizeof degree);
	memset(visit, 0, sizeof visit);
	ne = 0;
	c = 0;
}

bool cmp(char* a, char*b) {
	return strcmp(a, b) > 0;
}

int main() {
	//inoutfile;
	bool first = true;
	while (true) {
		init();
		if (scanf("%c ", nodes + n++) == EOF){
			return 0;
		}
		else if (!first) {
				puts("");		
		}
		else
			first = 0;

		while (true) {
			scanf("%c%c", nodes + n++, &nl);
			if (nl == '\n') break;
		}
		while (true) {
			char a, b;
			scanf("%c %c%c", &a, &b, &nl);
			add_edge(a, b);
			if (nl == '\n') break;
		}
		TOPO();
		sort(allres.rbegin(), allres.rend(),cmp);
		for (int j = 0; j < allres.size(); ++j) {
			printf("%s\n", allres[j]);
		}
		
		allres.clear();
	}
}