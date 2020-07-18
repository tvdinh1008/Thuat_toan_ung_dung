#include<iostream>
#include<vector>
#include<queue>
#define MAX 101
using namespace std;

int N, M, K;
int b[MAX];
int e[MAX];
int c[MAX];
int X[MAX];//solution của bài toán
int sumW;
int result;

int r[MAX];
int p[MAX];

int d[MAX];//


void maketSet(int x)
{
	p[x] = x;
	r[x] = 0;
}
void link(int x,int y)
{
	if (r[x] > r[y]) p[y] = x;
	else
	{
		p[x] = y;
		if (r[x] = r[y]) r[y] = r[y] + 1;
	}
}
int findSet(int x)
{
	if (p[x] != x)
	{
		p[x] = findSet(p[x]);
	}
	return p[x];
}
void input()
{
	cin >> N >> M >> K;
	int u, v, w;
	for (int i = 1; i <= M; i++)
	{
		cin >> u >> v >> w;
		b[i] = u;
		e[i] = v;
		c[i] = w;

	}
}

//
void init()
{
	for (int i = 1; i <= N; i++) {
		d[i] = -1;
	}
}
int findMax()
{
	int max_d = -1;
	int u = -1;
	for (int i = 1; i <= N; i++)
	{
		if (max_d < d[i]) {
			max_d = d[i];
			u = i;
		}
	}
	return u;
}
void BFS(int s, vector<int> A[])
{
	queue<int>q;
	q.push(s);
	d[s] = 0;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (int i = 0; i < A[v].size(); i++)
		{
			int u = A[v][i];
			if (d[u]<0)
			{
				d[u] = d[v] + 1;
				q.push(u);
			}		
		}
	}
}
//tính đường kính của cây( gần giống với longest path on a tree)
int diameter()
{
	vector<int> A[MAX];
	for (int i = 1; i <= N - 1; i++)
	{
		int u = b[X[i]]; int v = e[X[i]];
		A[u].push_back(v);
		A[v].push_back(u);
	}
	init();
	BFS(1, A);
	int u = findMax();
	init();
	BFS(u, A);
	u = findMax();
	return d[u];	
}
void solution()
{
	int dia = diameter();
	if (dia <= K) {
		if (sumW < result)
		{
			result = sumW;
		}
	}
}
//ktra xem có tạo thành chu trình hay ko
bool check(int v, int k)
{
	for (int v = 1; v <= N; v++) maketSet(v);
	for (int i = 1; i < k; i++)
	{
		int u = b[X[i]]; int v = e[X[i]];
		int p_u = findSet(u); int p_v = findSet(v);
		if (p_u == p_v)
		{
			return false;
		}
		link(p_u, p_v);
	}
	if (findSet(b[v]) == findSet(e[v])) return false;
	return true;
}
void Try(int k)
{
	for (int v = X[k - 1] + 1; v <= M; v++)
	{
		if (check(v, k))
		{
			X[k] = v;
			sumW += c[v];
			//Đồ thị có N đỉnh -> có N-1 cạnh
			if (k == N - 1)
			{
				solution();
			}
			else
			{
				Try(k + 1);
			}
			sumW -= c[v];
		}
	}
}
void solve()
{
	result = 9999999;
	X[0] = 0;
	sumW = 0;
	Try(1);
	if (result == 9999999) result = -1;
	cout << result;
}

int main()
{
	ios::sync_with_stdio(false);
	input();
	solve();
	return 0;
}