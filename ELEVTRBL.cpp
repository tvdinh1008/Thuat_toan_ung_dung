#include<iostream>
#include<queue>

#define MAX 1000001
using namespace std;
int f, s, g, u, d;
int Count[MAX];


void input()
{
	cin >> f >> s >> g >> u >> d;
}
//quy nó về đồ thị cho dễ
void bfs(int s)
{
	queue<int> q;
	q.push(s);
	Count[s] = 0;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		if (v == g) break;
		//bấm lên
		if (v + u <= f && Count[v + u] == -1)
		{
			q.push(v + u);
			Count[v + u] = Count[v] + 1;
		}
		//bấm xuống
		if (v - d >= 1 && Count[v - d] == -1)
		{
			q.push(v - d);
			Count[v - d] = Count[v] + 1;
		}
	}
}

void solve()
{
	for (int i = 1; i <= f; i++)
	{
		Count[i] = -1;
	}
	bfs(s);
	if (Count[g] != -1)
	{
		cout << Count[g];
	}
	else
	{
		cout << "use the stairs";
	}
}
int main()
{
	ios::sync_with_stdio(false);
	input();
	solve();
	return 0;
}