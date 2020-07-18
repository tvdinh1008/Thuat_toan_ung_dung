//hành trình cho tắc xi
#include<iostream>
#include<string.h>
#include<string>
#define MAX 100001
using namespace std;
int N;
int x[MAX];//hoán vị của 1,2,3,....2N
int appear[MAX];//1 là xuất hiện rồi
char S[MAX];
int K;
char tmp[MAX];
char result[MAX];

//i là điểm đón và N+i là điểm trả
void solution()
{
	for (int i = 1; i <= K; i++)
	{
		result[i - 1] = S[x[i]];
	}
	result[K] = 0;
	if (strcmp(result, tmp) > 0)
	{
		strcpy(tmp, result);
	}
}
bool check(int v, int k)
{
	if (x[k - 1] > v) return 0;
	return appear[v] == 0;
}
void TRY(int k)
{
	for (int v = 0; v < N; v++)
	{
		if (check(v, k))
		{
			x[k] = v;
			appear[v] = 1;
			if (k == K) solution();
			else
			{
				for (int i = 1; i <= k; i++)
				{
					result[i - 1] = S[x[i]];
				}
				result[k] = 0;
				if (strcmp(result, tmp) > 0)
				{
					TRY(k + 1);
				}

			}
			appear[v] = 0;
		}
	}
	
}
void solve()
{
	//for (int i = 0; i < K; i++) tmp[i] = 0;
	tmp[0] = 0;
	x[0] = -1;
	for (int i = 0; i < N; i++) appear[i] = 0;
	TRY(1);
	cout << tmp;
}


int main()
{
	cin >> S;
	cin >> K;
	N = strlen(S);
	solve();
	return 0;
}