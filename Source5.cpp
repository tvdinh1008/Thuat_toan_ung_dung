#include<iostream>

#define MAX 1000001
using namespace std;
int b[MAX];//đỉnh đầu begin
int e[MAX];//đỉnh cuối
int N, M;
int X[MAX];//chứa chỉ số cạnh có 2 đỉnh u,v khi tìm lời giải

//struct disjoint set
int p[MAX];// p[v] is parent of v
int r[MAX];// r[v] is rank of set v

long long result;

//tìm cha của x và cập nhật quy hết về 1 cha(gán px=find)
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
//hợp 2 tập s1,s2 vào cùng 1 cha
void link(int x, int y)
{
	if (r[x] > r[y]) p[y] = x;
	else
	{
		p[x] = y;
		if (r[x] == r[y]) r[y] = r[y] + 1;
	}
}

bool checkNoCycle(int v, int k)
{
	for (int i = 1; i <= N; i++) makeSet(i);
	//duyệt từ cạnh 1 đến k-1
	for (int i = 1; i < k; i++)
	{
		int x = b[X[i]];
		int y = e[X[i]];
		int px = findSet(x);
		int py = findSet(y);
		if (px == py) return false;
		link(px, py);
	}
	//gán cha cho tập S xong. nếu cạnh mới thêm vào mà có đỉnh đầu cùng cha với đỉnh cuối->loại
	if (findSet(b[v]) == findSet(e[v])) return false;
	return true;
}

//k là số cạnh trong cây, v là tập cạnh. ta sẽ thử với tất cả các cạnh trong đồ thị
void duyet(int k)
{
	//đồ thị N đỉnh -> sẽ có N-1 cạnh nối
	if (k == N)
	{
		result++;
		return;
	}
	//tập cạch bắt đầu từ 1
	for (int v = X[k - 1] + 1; v <= M; v++)
	{
		if (checkNoCycle(v, k))
		{
			X[k] = v;
			duyet(k + 1);
		}
	}
}
void input()
{
	cin >> N;
	M = 3 * N - 2;
	
	int j = 1;
	for (int i = 1; i <= N; i++)
	{
		if (i < N)
		{
			b[j] = 2 * i;
			e[j] = 2 * i - 1;
			j++;

			b[j] = 2 * i - 1;
			e[j] = 2 * (i+1) - 1;
			j++;

			b[j] = 2 * i;
			e[j] = 2 * (i + 1);
			j++;
		}
		else
		{
			b[j] = 2 * N;
			e[j] = 2 * N - 1;
			j++;
		}
	}
	
	N = 2 * N;
}
void solve()
{
	result = 0;
	X[0] = 0;
	duyet(1);
	cout << result % 1000000007;
}
int main()
{
	input();
	solve();

	return 0;
}