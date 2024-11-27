#include<iostream>
#include <string>
using namespace std;
void main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;
            int length = word.size();
            if (length > 10)
            {
                cout << word[0] << length - 2 << word[length - 1] << endl;
            }
            else
            {
                cout << word << endl;
              
            }
        }
    }
