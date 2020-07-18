#include<iostream>
#include<vector>
#define MAX 100001

using namespace std;
vector<int> A[MAX];//đồ thị theo danh sách kề(chú ý là vô hướng ->cần pushback 2 phía)
int N, M;//N là số đỉnh của đồ thị, M là số cạnh của đồ thị vô hướng
int visited[MAX];//đánh dấu đỉnh đã được thăm
int result;

void input()
{
	cin >> N >> M;
	int u, v;
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
	}
}
void DFS(int v)
{
	visited[v] = 1;
	for (int i = 0; i < A[v].size(); i++)
	{
		int u = A[v][i];
		if (visited[u] == 0)
		{
			DFS(u);
		}
	}
}
void solve()
{
	result = 0;
	for (int i = 1; i <= N; i++) visited[i] = 0;
	for (int v = 1; v <= N; v++)
	{
		if (visited[v] == 0)
		{
			DFS(v);
			result++;
		}
	}
	cout << result;
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