#include<iostream>

#define MAX 20
using namespace std;
int N;
int d[MAX];
int day[MAX];
int result;
int main()
{
	result = 99999999;
	cin >> N;
	for (int i = 1; i <= N; i++) day[i] = 6;
	for (int i = 1; i <= N; i++)
	{
		cin >> d[i];
	}
	for (int j = 1; j <= N; j++)
	{
		for (int i = 1; i <= N; i++)
		{  
			if (d[j] <= day[i] && day[i] > 0)
			{
				day[i] -= d[j];
				break;
			}
		}

	}
	int Count = 0;
	for (int i = 1; i <= N; i++)
	{
		if (day[i] != 6)
		{
			Count++;
		}
	}
	if (Count < result) result = Count;
	cout << result;
	return 0;
}