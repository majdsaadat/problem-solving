#include<iostream>
using namespace std;
void main()
    {
		int wight;
		cout << "Please Enter The Wight to Watermelon : ";
		cin >> wight;
		if (wight >= 1 && wight <= 100)
		{
			if (wight % 2 == 0)
			{
				if (wight == 2)
				{
					cout << "NO" << endl;
				}
				else
				{
					cout << "YES" << endl;
				}
			}
			else
				cout << "NO" << endl;
			
		}
	}
