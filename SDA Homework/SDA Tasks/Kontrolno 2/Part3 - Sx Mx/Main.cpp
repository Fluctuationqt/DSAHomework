#include <string>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int S(int x, queue<int>& q)
{
	int sum = 0;
	bool contains = false;
	for (int i = 0; i < q.size(); i++)
	{
		int current = q.front();
		q.pop();

		if (current != x)
			sum += current;
		else
			contains = true;

		q.push(current);
	}

	if (contains && sum == x)
		return (x + x) % 10;
	else
		return x;
}

int M(int x, queue<int>& q)
{
	int prod = 1;
	bool contains = false;
	for (int i = 0; i < q.size(); i++)
	{
		int current = q.front();
		q.pop();

		if (current != x)
			prod *= current;
		else
			contains = true;

		q.push(current);
	}

	if (contains && prod == x)
		return (x * x) % 10;
	else
		return x;
}

int main()
{
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(6);
	string expression = "s(m(s(3)))";
	
	stack<char> st;
	for (int i = 0; i < expression.length(); i++)
	{
		char letter = expression[i];
		if (letter == 'm' || letter == 's' || (letter <= '9' && letter >= '0'))
		{
			st.push(letter);
		}
		else if (letter == ')')
		{
			int number = st.top() - '0'; 
			st.pop();
			char method = st.top();
			st.pop();

			if (method == 's')
				st.push(S(number, q) + '0');
			if (method == 'm')
				st.push(M(number, q) + '0');
		}
	}

	if (st.size() == 1)
		cout << st.top() - '0' << endl;
	else
		cout << "syntax error" << endl;
	return 0;
}