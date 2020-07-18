#include<iostream>

#define MAX 100001
using namespace std;

//lưu dữ liệu kiểu này sẽ dễ duyệt cạnh hơn(i=0->M-1)
int N, M;
int u[MAX];
int v[MAX];
int c[MAX];
int ET[MAX];// cây khung nhỏ nhất
int nET;

//cấu trúc disjoint set
int r[MAX];//is the rank of the set v 
int p[MAX];// is the perent of v
long long result;

void input()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> u[i] >> v[i] >> c[i];
	}

}
//desjoint set
void makeSet(int x)
{
	p[x] = x;//ban đầu cha của x là x
	r[x] = 0;//rank =0
}
int findSet(int x) //tìm cha của v
{
	if (x != p[x])
	{
		p[x]=findSet(p[x]);//có tác dụng quy hết về 1 cha sau quá trình đệ quy
	}
	return p[x];
}
void link(int x, int y)//hợp 2 tập hợp có cha là x và y vào thành 1 tập
{
	if (r[x] > r[y])
	{
		p[y] = x;
	}
	else //r[x]<=r[y]
	{
		p[x] = y;
		if (r[x] == r[y]) r[y] = r[y] + 1;//do khi = ta đã gắn cha của x là y
	}
}
//end desjoint set
void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
void swapEdge(int i, int j)
{
	swap(c[i], c[j]);
	swap(u[i], u[j]);
	swap(v[i], v[j]);
}
int partition(int L, int R)
{
	int i, j, p;
	i = L+1;
	j = R;
	p = c[L]; //lấy phần tử đầu tiên ra so sánh
	while (i <= j)
	{
		while (i <= R && c[i] < p) i++;
		while (j >= L && c[j] > p) j--;
		if (i > j)
		{
			break;
		}
		swapEdge(i, j);
		i++;
		j--;
	}
	swapEdge(L, j);
	return j;
}
void QuickSort(int L, int R)
{
	if (L < R)
	{
		int pivot = partition(L, R);
		if (L < pivot)
		{
			QuickSort(L, pivot - 1);
		}
		if (R > pivot)
		{
			QuickSort(pivot + 1, R);
		}
	}
}

void solve()
{
	result = 0;
	nET = 0;
	int count = 0;
	for (int v = 1; v <= N; v++) makeSet(v);
	//sắp xếp các cặp đỉnh theo thứ tự giảm của C[i]
	QuickSort(0, M - 1);

	for (int i = 0; i < M; i++)
	{
		int ru = findSet(u[i]);
		int rv = findSet(v[i]);
		if (ru != rv)
		{
			link(ru, rv); 
			nET++;
			ET[nET] = i;
			result += c[i];
			count++;
			if (count == N - 1)
			{
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