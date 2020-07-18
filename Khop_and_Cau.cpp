/*
	Khớp là đỉnh mà việc loại bỏ nó làm tăng số thành phần liên thông của đồ thị
	Cầu là cạnh mà việc loại bỏ nó làm tăng số thành phần liên thông của đồ thị
	*Ý tưởng:
	+Khớp:
		Duyệt DFS(): nếu bất kỳ node con nào không cạnh ngược(ko có đường đi từ con cháu tới tổ tiên)->loại bỏ nó sẽ làm tăng tp liên thông đồ thị(ko có đường đi tới cha)
		ngoại lệ đỉnh gốc của DFS là khớp nếu gốc đó có 2 con trực tiếp trở lên
	+Cầu:
*/
#include<iostream>
#include<vector>
using namespace std;
#define MAX 100001
int N, M;
vector<int> A[MAX];

bool Node[MAX];//đánh dấu khớp
int Edge = 0;//số cầu

int Num[MAX];//Num[u] là thứ tự duyệt của đỉnh u trong dfs
int Low[MAX];// giá trị Num[u] nhỏ nhất đạt được trong dãy dfs con của đỉnh u, ban đầu Low[u]=Num[u]. giá trị có thể giảm nếu duyệt chu trình có 3 đỉnh trở lên
int time=0;//thời gian đến thăm

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

int min(int a,int b)
{
	return (a < b) ? a : b;
}

//p là cha, u là con
void DFS(int u,int p)
{
	int numChild = 0;//đếm xem có mấy con
	Num[u] = Low[u] = ++time;

	for (int i = 0; i < A[u].size(); i++)
	{
		int v = A[u][i];
		if (v != p) //nếu không phải là con trực tiếp
		{
			if (Num[v] != 0) //nếu đã được thăm-> v là tổ tiên của u
			{
				Low[u] = min(Low[u], Num[v]);
			}
			else {
				DFS(v, u);
				numChild++;
				Low[u] = min(Low[u], Low[v]);
				//nếu sau khi cập nhật mà low vẫn nhỏ hơn num-> v chỉ có thể đến đc từ u nhưng ko bao trùm u vì bao trùm thì -> low[v] sẽ cập nhật nhỏ hơn Num
				if (Low[v] >= Num[v]) 
				{
					Edge++;
				}

				if (u == p)//trường hợp ngoại lệ cho khớp(root)
				{
					if (numChild >= 2)
					{
						Node[u] = true;
					}
				}
				else
				{
					//tức con v có low[v] < Num[u] thì DFS(v, u) đã cập nhật low[v] hay v có đường đi tới tổ tiên nó(khác cha)
					if (Low[v] >= Num[u])
					{
						Node[u] = true;
					}
				}

			}

		}
	}



}

void solve()
{
	for (int i = 1; i <= N; i++) {
		Node[i] = 0;
		Num[i] = 0;
	}

	for (int i = 1; i <= N; i++)
	{
		if (Num[i] == 0)
		{
			DFS(i, i);
		}
	}

	int Count = 0;
	for (int i = 1; i <= N; i++)
	{
		if (Node[i] == 1)
		{
			Count++;
		}
	}
	cout << Count << " " << Edge;//khớp và cầu nối
}
int main()
{
	input();
	solve();
	return 0;
}
/*
Giải thuật DFS đỉnh u được tiến hành như sau: Đặt num[u] = low[u] = ++time. 
Với mỗi đỉnh v kề với u, ta chia ra hai trường hợp:
	•Nếu v chưa thăm:
		(a) Ghi nhận đỉnh u là cha của đỉnh v trên cây DFS.
		(b) Nếu đỉnh u là gốc của cây DFS, cập nhật số lượng con của nó.
		(c) DFS(v)
		(d) Nếulow[v] >= num[u](từ v chỉ có thể đi đến một đỉnh từ u trở xuống trên cây DFS), thì u là khớp. Vì nếu không có u thì mọi đỉnh từ v trở xuống không đế nđược những đỉnh trên u.
		(e) Nếulow[v] > num[u](từ v chỉ có thể đi đến một đỉnh dưới u nhưng không bao gồm u trên cây DFS) thì cạnh (u,v) là cầu
		(f) Tối thiểu giá trị low[u] theo giá trị low[v].
	•Nếu v đã thăm (chúng ta có một chu trình) và v không phải là cha của u (chu trình có hơn 2 đỉnh) thì tối thiểu low[u] theo num[v].
*/