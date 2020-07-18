/*  Định lý:
	+ Đa đồ thị vô hướng liên thông(từ 1 đỉnh bất kỳ đến tất cả các đỉnh còn lại) ta có chu trình euler <-> nó không có đỉnh bậc lẻ
	+ Đa đồ thị vô hướng liên thông(từ 1 đỉnh bất kỳ đến tất cả các đỉnh còn lại) ta có đường đi euler <-> nó không có quá 2 đỉnh bậc lẻ
	bậc của đỉnh là số cạnh ra từ 1 đỉnh
	cách làm : b1: ktra tính liên thông của đồ thị vô hướng
			   b2: ktra định lý
*/
#include<iostream>
#include<vector>
using namespace std;
#define MAX 10001

vector<int> A[MAX];
int N, M;
int marked[MAX];

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
void dfs(int v)
{
	marked[v] = 1;
	for (int i = 0; i < A[v].size(); i++)
	{
		int u = A[v][i];
		if (marked[u] == 0)
		{
			dfs(u);
		}
	}
}
bool isConnectedComponent()
{
	for (int i = 1; i <= N; i++) marked[i] = 0;
	dfs(1);

	bool flag = true;
	for (int i = 1; i <= N; i++)
	{
		flag &= marked[i];
	}
	return flag;
}

int isEuler()
{
	if (!isConnectedComponent())
	{
		return 0;
	}
	int d = 0;
	for (int i = 1; i <= N; i++)
	{
		d += (A[i].size() % 2);
	}
	if (d > 2)
	{
		return 0;
	}
	return (d) ? 2 : 1;
}
void solve()
{
	//0 tức ko phải euler, 1 là cycle, 2 là path
	int tmp = isEuler();
	if (tmp == 1)
	{
		cout << "Euler cycle";
	}
	else if (tmp == 2)
	{
		cout << "Euler path";
	}
	else
	{
		cout << "Not graph euler";
	}
}
int main()
{
	input();
	bool k= isConnectedComponent();
	solve();
	return 0;
}
/*
//chu trình euler
6 8
1 2
1 3
2 6
2 5
2 4
3 4
4 5
4 6
//đường đi euler
5 7
1 2
1 3
1 4
2 4
2 5
3 4
4 5
//
6 6
1 2
1 3
2 6
2 4
3 4
4 6
*/
