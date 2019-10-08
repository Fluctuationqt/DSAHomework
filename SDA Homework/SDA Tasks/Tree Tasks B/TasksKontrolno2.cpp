/*
	TasksKontrolno2.cpp : This file contains the solution to the tasks in kontrolno2 SDA january 2018
	Problems are in the project folder as an *.html file
*/

#include "stdafx.h"
#include <iostream>

// Data Structures
#include "tree.hpp"  // used in task1 and task2
#include "Queue.hpp" // used in task2
#include "LStack.hpp"
#include <list>      // used in task2 and Graph.hpp
#include "Graph.hpp" // used in task3
// Solutions
#include "Task1.hpp"
#include "Task2.hpp"
#include "Task3.hpp"

using namespace std;

void Task1Example()
{
	Tree<int> tree;
	tree.initTestTree();
	cout << "Sum is: " << SumElementsWithEvenCountOfDescendantsInRange(tree.getRoot(), 4, 10) << endl;
}

void Task2Example1()
{
	Tree<int> a, b;

	a.initTestTree();
	b.initTestTree2();

	list<list<int>*>* a_levels = GetLevels(a.getRoot());
	list<list<int>*>* b_levels = GetLevels(b.getRoot());

	if (CompareLevels(a_levels, b_levels))
		cout << "Levels are matching" << endl;
	else
		cout << "Levels are not matching" << endl;
}

void Task2Example2()
{
	Tree<int> a, b;

	a.initTestTree();
	b.initTestTree();

	list<list<int>*>* a_levels = GetLevels(a.getRoot());
	list<list<int>*>* b_levels = GetLevels(b.getRoot());

	if (CompareLevels(a_levels, b_levels))
		cout << "Levels are matching" << endl;
	else
		cout << "Levels are not matching" << endl;
}

void Task2Example3()
{
	Tree<int> a, b;

	a.initTestTree();
	b.initTestTreeSym();

	list<list<int>*>* a_levels = GetLevels(a.getRoot());
	list<list<int>*>* b_levels = GetLevels(b.getRoot());

	if (CompareLevels(a_levels, b_levels))
		cout << "Levels are matching" << endl;
	else
		cout << "Levels are not matching" << endl;
}




void Task3()
{
	Graph<string> friends;
	friends.FromFile("friends.txt");
	friends.Print();
	cout << endl << endl;


	SendMail(&friends, "Petya", "Grigorka");
}

int main()
{
	/* Comment/Uncomment to run an example */

	//Task1Example();
	
	 //Task2Example1();
	 //Task2Example2();
	 //Task2Example3();
	 Task3();



	
    return 0;
}

