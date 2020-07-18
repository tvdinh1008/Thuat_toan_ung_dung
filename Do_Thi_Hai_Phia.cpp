#include<iostream>
#include<vector>
#include<queue>
#define MAX 100001
using namespace std;
int N, M;
vector<int> A[MAX];//kiểm tra đồ thị vô hướng có phải là đồ thị 2 phía
int d[MAX];
int result;//=1 nếu là đồ thị 2 phía
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
int depth;
void init()
{
	for (int i = 1; i <= N; i++) d[i] = -1;
	depth = 0;
}

int BFS(int s)
{

	queue<int> q;
	q.push(s);
	d[s] = 0;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		//kiểm tra đỉnh vừa lấy ra v với các đỉnh cho vào u có thỏa mãn điều kiện?
		for (int i = 0; i < A[v].size(); i++)
		{
			int u = A[v][i];
			if (d[u]!=-1)
			{
				if (d[v] % 2 == d[u] % 2) return 0;
			}
			else
			{
				d[u] = d[v] + 1;
				q.push(u);
			}
		}
	}
	return 1;
}

void solve()
{
	init();
	result = 1;
	for (int v = 1; v <= N; v++)
	{
		if (d[v] == -1)
		{
			if (BFS(v)==0)
			{
				result = 0;
				break;
			}
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