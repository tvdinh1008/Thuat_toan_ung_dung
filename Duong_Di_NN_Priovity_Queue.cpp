#include<iostream>
#include<vector>
#define MAX 100001
using namespace std;
vector<int> A[MAX];//ds kề
vector<int> C[MAX]; //trọng số của cạnh
int N, M;
int s, t;//tìm đường đi ngắn nhất từ s->t
int result;
//mỗi 1 node trên cây sẽ chứa đỉnh v và d[v]
int node[MAX];//chứa đỉnh v
int idx[MAX];//là chỉ số của v trong mảng node
int d[MAX];//trọng số đường đi tại đỉnh v:  d[v]
bool fixed_v[MAX];//đánh dấu đỉnh v đã được chọn trong đường đi hay chưa
int sH;//size của heap

//priority queues
void swap(int i, int j)
{
	//đổi đỉnh trong node
	int tmp = node[i];
	node[i] = node[j];
	node[j] = tmp;
	//đổi chỉ số v trong mảng
	idx[node[i]] = i;
	idx[node[j]] = j;

}
//cập nhật từ con(chỉ số i->cha sẽ là i-1/2) đến root
void upheap(int i)
{
	if (i == 0) return;
	while(i>0)
	{
		int parent_i = (i - 1) / 2;
		if (d[node[parent_i]] > d[node[i]])
		{
			swap(parent_i, i);
		}
		else
		{
			break;
		}
		i = parent_i;//cập nhật từ vị trí parent lên tới root
	}
}
//cập nhật từ cha đến các con
void downheap(int i)
{
	int L = 2 * i + 1;
	int R = 2 * i + 2;
	//tìm phần tử nhỏ nhất trong cha và 2 con
	int midx = i;
	if (L<sH && d[node[L]] < d[node[midx]]) midx = L;
	if (R<sH && d[node[R]] < d[node[midx]]) midx = R;
	if (midx != i)
	{
		swap(i, midx);
		//do đẩy vị trí con lên trên -> có thể tại vị trí con đó cần cập nhật trong TH cha là midx lớn hơn con của midx
		downheap(midx);
	}
}
void insert(int v,int dv)
{
	d[v] = dv;
	node[sH] = v;
	idx[v] = sH;
	//quy tắc insert là lấp đầy cây, insert từ trái qua phải-> khi insert vào lá thì cha của nó có thể ko thỏa mãn
	upheap(sH);
	sH++;
}
//cập nhật dv của đỉnh v trong cây 
void updateKey(int v, int k)
{
	if (d[v] > k)
	{
		d[v] = k;
		//vì dv nhỏ hơn -> có thể cha của nó ko thỏa mãn
		upheap(idx[v]);
	}
	else
	{
		d[v] = k;
		//dv lớn hơn->có thể con của nó nhỏ hơn dv-> cập nhật
		downheap(idx[v]);
	}
}
//ktra đỉnh v có trong heap?
bool inheap(int v)
{
	return idx[v] >= 0;
}
//delete trả về đỉnh v mà nó vừa xóa khỏi cây
int deleteMin()
{
	int sel_node = node[0];
	swap(0, sH - 1);
	sH--;
	downheap(0);
	return sel_node;
}
//end priority queues


void input()
{
	cin >> N >> M;
	int u, v, w;
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v >> w;
		A[u].push_back(v);
		C[u].push_back(w);
	}
	cin >> s >> t;
}
void init(int s)
{
	sH = 0;
	for (int i = 1; i <= N; i++)
	{
		idx[i] = -1;
		fixed_v[i] = false;
	}
	d[s] = 0;
	fixed_v[s] = true;
	for (int i = 0; i < A[s].size(); i++)
	{
		int u = A[s][i];
		insert(u, C[s][i]);
	}
}
void solve()
{
	init(s);
	while (sH > 0)
	{
		int u = deleteMin();
		fixed_v[u] = 1;//dánh dấu đã cho vào đường đi

		for (int i = 0; i < A[u].size(); i++)
		{
			int v = A[u][i];
			if (fixed_v[v] == true)
			{
				continue;
			}
			//v chưa có trong heap
			if (inheap(v) == 0)
			{
				int w = d[u] + C[u][i];
				insert(v, w);
			}
			else
			{
				if(d[v]>d[u]+C[u][i])
				updateKey(v, d[u] + C[u][i]);
			}
		}
	}
	result = d[t];
	if (fixed_v[t] == false)
	{
		result = -1;
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