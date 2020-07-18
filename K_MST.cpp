#include<iostream>
#include<vector>
#include<set>
#define MAX 1000001
using namespace std;
int N, M, K;

int w[MAX];
int b[MAX];
int e[MAX];
int X[MAX];
int sumW, result;

int visited[MAX];
//sử dụn set vì set chỉ lưu giá trị khác nhau mà khi insert ta inset cả b[i] và e[i] nếu trùng nó lấy 1 giá trị-> Ax chỉ lưu đỉnh mà nó chọn cho solution
set<int> Ax[MAX];//kiểm tra các cạch đc chọn có tọa đc thành 1 cây hay không sử dụn dfs tại 1 đỉnh nếu tổng dfs=1 ->là cây

//data structure disjoint set
int p[MAX];
int r[MAX];

int findSet(int x)
{
	if (x != p[x])
	{
		p[x] = findSet(p[x]);
	}
	return p[x];
}
void makeSet(int x)
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
		if (r[x] == r[y]) r[y] = r[y] + 1;
	}
}
void swap(int& x,int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}
void swapEdge(int i,int j)
{
	swap(b[i], b[j]);
	swap(e[i], e[j]);
	swap(w[i], w[j]);
}
int partition(int L,int R,int index)
{
	int pivot = w[index];
	swapEdge(R, index);
	int storeIndex = L;
	for (int i = L; i <= R - 1; i++)
	{
		if (w[i] < pivot)
		{
			swapEdge(i, storeIndex);
			storeIndex++;
		}
	}
	swapEdge(storeIndex, R);
	return storeIndex;
}
void QuickSort(int L,int R)
{
	if (L < R)
	{
		int index = (R + L) / 2;
		index = partition(L, R, index);
		if (L < index)
		{
			QuickSort(L, index - 1);
		}
		if (R > index)
		{
			QuickSort(index + 1, R);
		}
	}
}
void input()
{
	cin >> N >> M >> K;
	int u, v, c;
	for (int i = 1; i <= M; i++)
	{
		cin >> u >> v >> c;
		b[i] = u;
		e[i] = v;
		w[i] = c;
	}
}

void DFS(int u)
{
	visited[u] = 1;
	for (set<int>::iterator it = Ax[u].begin(); it != Ax[u].end(); it++)
	{
		int v = *it;
		if (visited[v] == 0)
		{
			DFS(v);
		}
	}
}
bool checkConnection()
{
	//lấy tất cả đỉnh
	set<int> Vx;
	for (int i = 1; i <= K; i++)
	{
		Vx.insert(b[X[i]]);
		Vx.insert(e[X[i]]);
	}
	// đánh dấu các đỉnh là chưa thăm
	for (set<int>::iterator it = Vx.begin(); it != Vx.end(); it++)
	{
		int u = *it;
		visited[u] = 0;
	}
	//
	int cnt = 0;
	for (set<int>::iterator it = Vx.begin(); it != Vx.end(); it++)
	{
		int u = *it;
		if (visited[u] == 0)
		{
			cnt++;
			DFS(u);
		}
	}
	return cnt==1;
}
void solution()
{
	if (checkConnection())
	{
		if (sumW < result) result = sumW;
	}
}
bool check(int v,int k)
{
	for (int i = 1; i <= N; i++) makeSet(i);
	for (int i = 1; i <= k - 1; i++)
	{
		int x = b[X[i]];
		int y = e[X[i]];
		int p_x = findSet(x);
		int p_y = findSet(y);
		if (p_x == p_y) return false;
		link(p_x, p_y);
	}
	if (findSet(b[v]) == findSet(e[v])) return false;
	return true;
}

void Try(int k)
{
	for (int v = X[k - 1] + 1; v < M - K + k; v++)//vì chỉ duyệt khi v còn đủ K cạnh thôi
	{
		if (check(v, k))
		{
			X[k] = v;
			sumW += w[v];
			Ax[b[v]].insert(e[v]);
			Ax[e[v]].insert(b[v]);
			if (k == K)
			{
				solution();
			}
			else
			{
				int g = sumW;
				for (int j = 1; j < K - k; j++)
				{
					g += w[X[k] + j];//do mảng w đc sắp xêp mà khi duyệt lại duyệt từ thấp-> cao
				}
				if (g < result)
				{
					Try(k + 1);
				}
			}
			sumW -= w[v];
			Ax[b[v]].erase(e[v]);
			Ax[e[v]].erase(b[v]);
		}
	}
}

/*
 Bài toán: tìm đồ thị có k cạnh sao cho sumWeigh là min
 sắp xếp các cạnh của đồ thị theo thứ tự từ thấp ->cao
 thử với các trường hợp cạnh . mỗi lần thử ktra xem có chu trình hay không?
 khi chọn đc K cạnh rồi.-> đc một lời giải 
 kiểm tra lời giải tập cạnh đc chọn có tạo đc 1 cây hay không vd 1->2->4->3 thì dfs =1. nếu 1->2 4->3 thì dfs=2
*/

void solve()
{
	QuickSort(1, M);
	sumW = 0;
	result = 999999;
	X[0] = 0;
	Try(1);
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
