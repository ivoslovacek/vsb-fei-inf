#include <iostream>
#include <string>
#include <stack>

using namespace std;



bool checkParity(string str)
{
	stack<char> s;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			s.push(str[i]);
		}

		if (str[i] == ')')
		{
			if (s.empty())
			{
				return false;
			}
			s.pop();
		}
	}

	if (s.empty())
		return false;
	else 
		return true;
}

int gcd(int m, int n)
{
	if (n == 0)
	{
		return m;
	}

	return gcd(n, m % n);
}

int gcd2(int m, int n)
{
	int tmp;

	while (n != 0)
	{
		tmp = m;
		m = n;
		n = tmp % n;
	}



	return m;
}

int main()
{
	string text = ("((())((())))");

	cout << "Text is " << (checkParity(text) ? "Ok" : "Crappy") << "." << endl;

	cout << gcd(86, 42) << endl << gcd2(15, 10) << endl;

	return 0;
}