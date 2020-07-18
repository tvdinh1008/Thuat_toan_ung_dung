#include<iostream>
#include<set>
#define MAX 20
using namespace std;
set<int> A[MAX];
int N, M;
int result;
int best_x[MAX];
int x[MAX];

void input()
{
	cin >> N >> M;
	int u, v;
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v;
		A[u].insert(v);
		A[v].insert(u);
	}
}
bool check(int v, int k)
{
	//k-2 do k-1 đã kề với k rồi ta cần kiểm tra các đỉnh còn lại thôi
	for (int i = 1; i <= k - 2; i++)
	{
		if (A[x[i]].find(v) == A[x[i]].end()) return false;
	}
	return true;
}
void Try(int k)
{
	//duyệt từ đỉnh 1 ta sẽ kiểm tra tất cả các đỉnh kề với 1 khi đó ta biết đc X[1,2..k-1] ktra k có thỏa mãn
	for (set<int>::iterator it = A[x[k - 1]].begin(); it != A[x[k - 1]].end(); it++)
	{
		int v = *it;
		if (check(v, k))
		{
			x[k] = v;
			if (k > result)
			{
				result = k;
				for (int i = 1; i <= k; i++) best_x[i] = x[i];
			}
			if (k < N)
			{
				Try(k + 1);
			}
		}
	}
}
void solve()
{
	result = 1;
	//ktra tất cả các đỉnh
	for (int i = 1; i <= N; i++)
	{
		x[1] = i;
		Try(2);
	}
	cout << result<<endl;
	//for (int i = 1; i <= result; i++) cout << best_x[i] << " ";
}

int main()
{
	ios::sync_with_stdio(false);
	input();
	solve();


	return 0;
}