#include<iostream>
#include<vector>
#include<queue>
#define MAX 100001
using namespace std;
vector<int> A[MAX];
int N;
int parent[MAX];
int color[MAX];


void input()
{
	cin >> N;
	int u, v;
	for (int i = 1; i < N; i++)
	{
		cin >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
	}
}

void bfs(int s)
{
	queue<int> q;
	q.push(s);
	parent[s] = s;//root
	for (int i = 1; i <= N; i++) color[i] = 0;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		color[v] = 1;
		for (int i = 0; i < A[v].size(); i++)
		{
			int u = A[v][i];
			if (color[u] == 0)
			{
				parent[u] = v;
				q.push(u);
			}
		}
	}
}
void solve()
{
	bfs(1);
	for (int i = 2; i <= N; i++) cout << parent[i] << " ";
}

int main()
{
	input();
	solve();

	return 0;
}