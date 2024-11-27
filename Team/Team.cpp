#include<iostream>
using namespace std;
int main()
{
	int numberOfProblem;
	cin >> numberOfProblem;
	bool a, b, c;
	int T1=0;
	int T2 = 0;
	if (numberOfProblem >= 1 && numberOfProblem <= 1000)
	{
		for (int i = 1; i <= numberOfProblem; i++)
		{
			cin >> a >> b >> c;
			if (a == 1 && b==1 )
			{
				T1 += 1;
			}
			else if (b == 1 && c == 1)
			{
				T1 += 1;
			}
			else if (a==1 && c == 1)
			{
				T1 += 1;
			}
		}
		
		cout << T1;
		
	}
}
