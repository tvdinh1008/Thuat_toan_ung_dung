#include<iostream>
#include<vector>
#include<queue>
#define MAX 100001
using namespace std;
vector<int> A[MAX];
vector<int> C[MAX]; //trọng số của cạnh
int N;

int d[MAX]; //là khoảng cách từ node nguồn đến v trong BFS
int p[MAX]; //p[v] là cha của v trong BFS


void input()
{
	cin >> N;
	int u, v,w;
	for (int i = 1; i <= N - 1; i++)
	{
		cin >> u >> v >> w;
		A[u].push_back(v);
		A[v].push_back(u);

		C[v].push_back(w);
		C[u].push_back(w);
	}
}

void init()
{
	for (int i = 1; i <= N; i++)
	{
		d[i] = -1;
		p[i] = -1;
	}
}
void BFS(int s)
{
	queue<int> q;
	d[s] = 0;
	q.push(s);

	while (!q.empty())
	{
		int v = q.front();
		q.pop();

		for (int i = 0; i < A[v].size(); i++)
		{
			int u = A[v][i];
			if (d[u] > -1)
			{
				if (p[v] != u)
				{
					//cout << "False" << endl;
				}
				continue;
			}
			int w = C[v][i];
			q.push(u);
			d[u] = d[v] + w;
			p[u] = v;

		}
	}

}
int findMax()
{
	int max_d = -1;
	int u = -1;
	for (int v = 1; v <= N; v++)
	{
		if (max_d < d[v])
		{
			max_d = d[v];
			u = v;
		}
	}
	return u;
}

void solve()
{
	init();
	BFS(1);
	int u = findMax();
	init();
	BFS(u);
	u = findMax();
	cout << d[u];
}
   
int main()
{
	input();
	solve();
	
	return 0;
}