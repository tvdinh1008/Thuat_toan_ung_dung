//Cycles of length k in an undirected and connected graph
//ý tưởng sử dụng dfs(từ đỉnh 1->N-K+1) đủ K cạnh thì kiểm tra xem điểm đầu có nối với đỉnh cuối không? loại bỏ đỉnh đã dfs xong ra khỏi đồ thị. chú ý 1 cycle sẽ đc duyệt 2 lần
#include<iostream>
#include<set>
using namespace std;
#define MAX 31
set<int> A[MAX];
int N, M, K;
int result;
int marked[MAX];//đánh dấu đỉnh đó đã duyệt dfs hay chưa

void input()
{
	cin >> N >> M >> K;
	int u, v;
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v;
		A[u].insert(v);
		A[v].insert(u);
	}
}
//đỉnh bắt đầu, duyệt đển đỉnh end kiểm tra xem end có trùng với start hay không?
void DFS(int start, int end, int k)
{
	marked[end] = 1;//đã thăm

	if (k == 1)
	{
		marked[end] = 0;
		if (A[end].find(start) != A[end].end())
		{
			result++;
			return;
		}
		return;
	}
	for (set<int>::iterator it = A[end].begin(); it != A[end].end(); it++)
	{
		int u = *it;
		if (marked[u] != 1)
		{
			DFS(start, u, k - 1);
		}
	}
	marked[end] = 0;
}
void solve()
{
	for (int i = 1; i <= N; i++) marked[i] = 0;
	result = 0;
	for (int i = 1; i <= N - K + 1; i++)
	{
		DFS(i, i, K);
		//loại bỏ đỉnh i ra khỏi đồ thị
		marked[i] = 1;
	}
	cout << result / 2;//do mỗi kết quả nó đc duyệt 2 lần
}

int main()
{
	input();
	solve();
	return 0;
}