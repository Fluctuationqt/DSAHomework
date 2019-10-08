#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

void print(stack<int> prev, stack<int> next)
{
	int count = prev.size();
	while (!prev.empty())
	{
		cout << prev.top();	prev.pop();
		if (!prev.empty())  cout << "+";
	}
	cout << "/" << count << " == " << next.top() << endl;
}

bool nextTopAverage(stack<int> prev, stack<int> next)
{
	int sum = 0, count = prev.size();
	while (!prev.empty())
	{
		sum += prev.top(); prev.pop();
	}

	if (sum / count == next.top())
		return true;
	
	return false;
}

int main()
{
	cout << "Are all of these true?" << endl;

	queue<stack<int>> q;
	q.push(stack<int>({ 1,2,3 }));
	q.push(stack<int>({ 2,2,2 }));
	q.push(stack<int>({ 1,6,2 }));
	q.push(stack<int>({7, 8, 9}));
	
	bool result = true;
	for(int i = 0; i < q.size(); i++)
	{
		stack<int> prev = q.front(); q.pop();
		result &= nextTopAverage(prev, q.front());
		print(prev, q.front());
		q.push(prev);
	}

	if (result)
		cout << "Yeap!" << endl;
	else
		cout << "Nope :(" << endl;

	return 0;
}