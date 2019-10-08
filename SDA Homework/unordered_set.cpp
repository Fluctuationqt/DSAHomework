#include "stdafx.h"
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main()
{
	unordered_set<string> s = { "A", "B", "C" };

	int n; cin >> n;
	string t;
	for (int i = 0; i < n; i++) {
		cin >> t;
		s.insert(t);
	}
	
	cout << endl;
	for (auto f : s) {
		cout << f << endl;
	}

	cout << endl;
	auto found = s.find("b");
	if (found == s.end())
		cout << "not found" << endl;
	else
		cout << "found" << *found << endl;
	return 0;
}