#include<iostream>
#include<vector>
using namespace std;
#define MAX 100001
vector<int> A[MAX];//danh sách kề của đồ thị có hướng N đỉnh, M cạnh
vector<int> A1[MAX];//đồ thị bù của A
int N, M;
int color[MAX];// W-white tức chưa được thăm, G-Gray là đã thăm nhưng chưa kết thúc, B-Black là đã kết thúc thăm
int idx;
int x[MAX];//lưu mảng đỉnh theo thứ tự kết thúc thăm sớm nhất-> muộn nhất
int t;
int finishtime[MAX];//đánh dấu thời điểm kết thúc thăm
int result;
int icc[MAX];//chỉ số các phần tử trong cùng 1 liên thông mạnh


void input()
{
	cin >> N >> M;
	int u, v;
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v;
		A[u].push_back(v);
		//A1[v].push_back(u);
	}
	for (int i = 1; i <= N; i++) color[i] = 'W';
}
void init()
{
	for (int i = 1; i <= N; i++) color[i] = 'W';
	t = 0;
}
//DFS A1
void DFS_A(int v)
{
	t++;
	color[v] = 'G';
	for (int i = 0; i < A[v].size(); i++)
	{
		int u = A[v][i];
		if (color[u] == 'W')
		{
			DFS_A(u);
		}
	}
	t++;
	finishtime[v] = t;
	color[v] = 'B';//đánh dấu kết thúc thăm
	idx++;
	x[idx] = v; //cho đỉnh v vào danh sách

}
void DFS_A()
{
	idx = 0;
	init();
	for (int v = 1; v <= N; v++)
	{
		if (color[v] == 'W')
		{
			DFS_A(v);
		}
	}
}
//xây dựng đồ thị bù từ danh sách kề của A
void buildResiduaGraph()
{
	for (int u = 1; u <= N; u++)
	{
		for (int i = 0; i < A[u].size(); i++)
		{
			int v = A[u][i];
			A1[v].push_back(u);
		}
	}
}
//DFS trên đồ thị bù
void DFS_A1(int v)
{
	t++;
	color[v] = 'G';
	icc[v] = result;
	for (int i = 0; i < A1[v].size(); i++)
	{
		int u = A1[v][i];
		if (color[u] == 'W')
		{
			DFS_A1(u);
		}
	}
	color[v] = 'B';

}
void DFS_A1()
{
	init();
	for (int i = N; i >= 1; i--) //duyệt từ đỉnh kết thúc thăm muộn nhất
	{
		int v = x[i];
		if (color[v] == 'W')
		{
			result++;
			DFS_A1(v);
		}
	}
}

void solve()
{
	result = 0;
	DFS_A();
	buildResiduaGraph();
	DFS_A1();
	cout << result;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	input();
	solve();
	/*
	for (int i = 1; i <= N; i++)
	{
		cout <<"  "<< icc[i] << endl;
	}
	*/
	return 0;
}