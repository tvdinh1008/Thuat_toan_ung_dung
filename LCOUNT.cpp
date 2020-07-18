#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define MAX 100001
vector<int> A[MAX];
int N;
int result;
int color[MAX];

void bfs(int s)
{
	queue<int> q;
	q.push(s);
	for (int i = 1; i <= N; i++) color[i] = 0;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		color[v] = 1;
		if (A[v].size() == 1 && v != 1)
		{
			result++;
		}
		for (int i = 0; i < A[v].size(); i++)
		{
			int u = A[v][i];
			if (color[u] == 0)
			{
				q.push(u);
			}
		}
	}
}

void input()
{
	cin >> N;
	int u, v;
	for (int i = 1; i <= N - 1; i++)
	{
		cin >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
	}
}
void solve()
{
	result = 0;
	bfs(1);
	cout << result;
}
int main()
{
	input();
	solve();

	return 0;
}