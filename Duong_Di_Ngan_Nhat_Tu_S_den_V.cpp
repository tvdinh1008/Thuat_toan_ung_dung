#include<iostream>
#include<vector>
#define MAX 100001
using namespace std;
vector<int> A[MAX];//ds kề
vector<int> C[MAX]; //trọng số của cạnh
int N, M;

int k[MAX];//đánh dấu 1 nếu cho đỉnh v vào đường đi ngắn nhất, =0 nếu chưa cho vào
int d[MAX]; //khoảng cách ngắn nhất hiện biết từ s->v
int p[MAX];//đỉnh đi trước v
int s, t;//tìm đường đi ngắn nhất từ s->t

vector<pair<int, int>> A[10];

void input()
{
	cin >> N >> M;
	int u, v, w;
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v >> w;
		A[u].push_back(v);
		C[u].push_back(w);
	}
	cin >> s >> t;
}
void init()
{
	for (int i = 1; i <= N; i++)
	{
		k[i] = 0;
		d[i] = 9999999;
		p[i] = -1;
	}
}
void solve()
{
	init();
	d[s] = 0;
	
	int count = 0;
	while (true)
	{
		int min_d = 9999999;
		int v = -1;
		for (int i = 1; i <= N; i++)
		{
			if (k[i] == 0)
			{
				if (d[i] < min_d)
				{
					min_d = d[i];
					v = i;
				}
			}
		}
		if (min_d == 9999999) break;
		if (v > 0)
		{
			k[v] = 1;
			count++;
			for (int i = 0; i < A[v].size(); i++)
			{
				int u = A[v][i];
				if (k[u] == 0)  
				{
					if (d[u] > d[v] + C[v][i])
					{
						d[u] = d[v] + C[v][i];
						p[u] = v;
					}
				}
			}
		}

		if (count == N)
		{
			break;
		}
	}
	if (k[t] == 1) {
		cout << d[t];
	}
	else
	{
		cout << -1;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	input();
	solve();
	return 0;
}