// RedBlackTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Tree.hpp"
using namespace std;

int main()
{
	Tree<int> tree;
	tree.Add(50);
	tree.Add(25);
	tree.Add(75);
	tree.Add(12);
	tree.Add(17);
	
	tree.Print();
	return 0;
}
