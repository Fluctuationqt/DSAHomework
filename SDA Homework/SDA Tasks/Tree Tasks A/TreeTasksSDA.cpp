/*
	################################################# TREE TASKS ###########################################################

	1. Да се напише функция, която извежда елементите на n-то ниво на дърво.

	2. Да се напише функция, която извежда листата на дърво, т.е. корените на поддърветата на дървото, които нямат наследници.

	3. Да се напише функция, която извежда елементите на дърво по нива (без да използва горната функция)

	4. Да се реализира функция, която намира височината на подаденото дърво

	5. Да се реализира функция, която намира елемент в дърво по “следа”. Следа наричаме поредица от символи ‘l’ и ‘r’,
	   които определят пътя от корена до даден елемент като на всяко ниво посочват дали да се тръгне по лявото или по
	   дясното поддърво. Например следа “lrr” означава, че за да се стигне до елемента трябва първо да се тръгне наляво
	   от корена, после надясно и пак надясно.

	6. Да се реализира функция, която търси елемент в дърво и ако го намери, връща следата към него.

	7. Да се реализира външна функция, която проверява дали едно двоично дърво е симетрично

	8. Да се реализира външна функция, която създава огледална версия на дърво

	9. Да се напише функция, която проверява дали съществува път между два елемента в рамките на дърво

	################################################# TREE TASKS ###########################################################
*/

#include "stdafx.h"
#include <iostream>
#include "tree.hpp"
#include "Queue.hpp"
#include "LStack.hpp"
#include <string>
using namespace std;

/* Task1 - Print nodes at given level in tree */
void printGivenLevel(Node<int>* root, int level)
{
	// if subtree is empty stop
	if (root == NULL)
		return;

	if (level == 1)
	{
		cout << root->data << " "; // terminal case, when level has become -1 we are at wanted level in subtrees
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);  // print left subtree and decrement level
		printGivenLevel(root->right, level - 1); // print right subtree and decrement level
	}
}

// Prints the tree levels line by line upto level
void printTreeToLevel(Node<int>* root, int level)
{
	cout << "Tree is:" << endl;
	cout << root->data << endl;
	for (int i = 1; i < level; i++)
	{
		printGivenLevel(root->left, i);
		printGivenLevel(root->right, i);
		cout << endl;
	}
	cout << "---------------" << endl;
}

/* Task2 - Print leaves of tree */
void printLeaves(Node<int>* root)
{
	// if tree is empty stop
	if (root == NULL)
		return;

	if (root->left == NULL && root->right == NULL)
		std::cout << root->data << " ";
	else
	{
		printLeaves(root->left);
		printLeaves(root->right);
	}
}

/* Task3 - Print level by level the tree */
template <typename T>
void printTree(Node<T>* root)
{
	if (root == NULL)
		return;

	// create a queue
	LQueue<Node<T>*> q;
	
	// push the root inside
	q.push(root);

	cout << "Tree is:" << endl;

	// loop until all levels are done
	while (true)
	{
		int nodeCountAtLevel = q.getSize(); // get queue size to find count of nodes at current level
		if (nodeCountAtLevel == 0) // if queue is empty then no more levels to look at
			break;
		
		// Dequeue all nodes at current level and enqueue nodes from next level
		while (nodeCountAtLevel > 0)
		{
			Node<T>* node;
			q.pop(node); // dequeue head of queue
			nodeCountAtLevel--; // decrement node count
			cout << node->data << " "; //print node from this level

			if (node->left != NULL)
				q.push(node->left); // enqueue left of current if it exists
			if (node->right != NULL)
				q.push(node->right); // enqueue right of current if it exists
		}
		cout << endl;
	}
	cout << "--------------" << endl;
}

/* TASK4 - get tree height from given root */
int maxDepth(Node<int>* root)
{
	if (root == NULL)
		return 0;
	else
	{
		// get left and right subtrees max depth and add 1 for current node
		int leftMaxDepth = 1 + maxDepth(root->left);
		int rightMaxDepth = 1 + maxDepth(root->right);

		// return the bigger subtree's depth
		if (leftMaxDepth >= rightMaxDepth)
			return leftMaxDepth;
		else
			return rightMaxDepth;
	}
}

/* TASK5 FIND NODE BY TRACE STRING (RRLLRL) */
Node<int>* getNodeByTrace(Node<int>* root, string trace)
{
	Node<int>* current = root;
	for (int i = 0; i < trace.length(); i++)
	{
		if (trace[i] == 'l')
			current = current->left;
		else if (trace[i] == 'r')
			current = current->right;
		else
		{
			std::cout << "Invalid Trace" << endl;
			return nullptr;
		}
	}
	return current;
}

/* TASK6 Find and return the trace and the path to an element given as a pointer */
bool FindNodeAndReturnTraceAndPath(Node<int>* root, Node<int>* searched, LStack<Node<int>*>& path, LStack<char>& trace)
{
	if (root == NULL)
		return false;
	
	
	// check if current is searched
	if (root == searched)
	{
		path.Push(root);
		return true;
	}
	// else check if searched is in left or right subtree
	bool inLeftSubtree = FindNodeAndReturnTraceAndPath(root->left, searched, path, trace);
	bool inRightSubtree = FindNodeAndReturnTraceAndPath(root->right, searched, path, trace);
	if ( inLeftSubtree || inRightSubtree )
	{
		if (inLeftSubtree)  trace.Push('l');
		if (inRightSubtree) trace.Push('r');
		path.Push(root);
		return true;
	}
	
	// if it wasn't found pop the nodes in this path
	
}

/* TASK7 Find if a tree is symetrical */
bool IsSymetrical(Node<int>* root)
{
	LQueue<Node<int>*> leftQ;
	LQueue<Node<int>*> rightQ;
	
	leftQ.push(root->left);
	rightQ.push(root->right);
	while (!leftQ.isEmpty() && !rightQ.isEmpty())
	{
		Node<int> *leftNode, *rightNode;
		leftQ.pop(leftNode);
		rightQ.pop(rightNode);
		if (leftNode == NULL && rightNode == NULL)
			continue;
		if (leftNode == NULL || rightNode == NULL)
			return false;

		if (leftNode->data != rightNode->data)
			return false;
		leftQ.push(leftNode->left);
		leftQ.push(leftNode->right);
		rightQ.push(rightNode->right);
		rightQ.push(rightNode->left);

	}
	if (!leftQ.isEmpty() && !rightQ.isEmpty())
		return false;
	
}

/* TASK8 Find a tree's mirror image */
void FlipTreeHorizontally(Node<int>* root)
{
	if (root == NULL)
		return;

	Node<int>* oldLeft = root->left;
	Node<int>* oldRight = root->right;
	
	root->left = oldRight;
	root->right = oldLeft;
	
	FlipTreeHorizontally(root->left);
	FlipTreeHorizontally(root->right);
}


void PathFromToo(Node<int>* root, Node<int>* searched1, Node<int>* searched2)
{
	LStack<Node<int>*> pathTo1;
	LStack<Node<int>*> pathTo2;
	LStack<char> traceTrash;
	if (!FindNodeAndReturnTraceAndPath(root, searched1, pathTo1, traceTrash) ||
		!FindNodeAndReturnTraceAndPath(root, searched2, pathTo2, traceTrash))
		throw std::exception("Element 1 or 2 not found");

	// find top most common in path
	Node<int>* common;
	while (true)
	{
		Node<int>* left;
		Node<int>* right;
		
		left = pathTo1.Pop();
		right = pathTo2.Pop();


		if (left == right && (pathTo1.Top() != pathTo2.Top()))
		{
			common = left;
			break;
		}
	}

	// flip path to 1
	LStack <Node<int>*> temp;
	while (!pathTo1.isEmpty())
	{
		temp.Push(pathTo1.Pop());
	}

	while (!temp.isEmpty())
		cout << temp.Pop()->data << " --> ";
	cout << common->data << " --> ";
	while (!pathTo2.isEmpty())
		cout << pathTo2.Pop()->data << " --> ";
	cout << endl;
	
}

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

int PushPop(int n, bool isPush)
{
	static LStack<int> st;
	if (isPush)
	{
		st.Push(n);
		return 1;
	}
	else
		return st.Pop();
}

Tree<char>* BuildTreeFromPrefix(string prefixExpr)
{
	
	LStack<Node<char>*> st;
	for (int i = prefixExpr.length() - 1; i >= 0; i--)
	{
		Node<char>* buildNode = new Node<char>;
		buildNode->data = prefixExpr[i];
		buildNode->left = NULL;
		buildNode->right = NULL;
		
		if (isDigit(buildNode->data))
		{
			st.Push(buildNode);
		}
		else
		{
	
			buildNode->left = st.Pop();
			buildNode->right = st.Pop();
			st.Push(buildNode);
			
		}
	}
	
	Tree<char>* tree = new Tree<char>(st.Pop());
	printTree(tree->getRoot());

	return tree;
}


// SOLUTIONS
int main()
{
	// create a  TEST tree
	Tree<int> tr;
	tr.initTestTree();

	 
	
	// TASK 1; #############################################################
	cout << "Level 3 of tree is: ";
	printGivenLevel(tr.getRoot(), 3);
	cout << endl;



	// TASK 2; #############################################################
	cout << "Leaves are: ";
	printLeaves(tr.getRoot());
	cout << endl << endl;



	// TASK 3; #############################################################
	printTree(tr.getRoot());
	/*
	 THIS IS WITH THE FUNCTION FOR LEVELS
	printTreeToLevel(tr.getRoot(), 5);
	cout << endl;
	*/



	// TASK 4; #############################################################
	cout << "Tree height is: " << maxDepth(tr.getRoot()) << endl << endl;




	// TASK 5; #############################################################
	cout << "Node at trace - rrll is:";
	Node<int>* found = getNodeByTrace(tr.getRoot(), "rrll");
	cout << found->data << endl;
	cout << endl;



	// TASK 6; #############################################################
	cout << "Searching for " << found->data << endl;
	LStack<Node<int>*> path;
	LStack<char> trace;
	if (FindNodeAndReturnTraceAndPath(tr.getRoot(), found, path, trace))
	{
		cout << "Trace is: ";
		while (!trace.isEmpty())
		{
			cout << trace.Pop() << " ";
		}
		cout << endl << "Path from root to searched is: ";
		while (!path.isEmpty())
		{
			cout << path.Pop()->data << " --> ";
		}
		cout << "NULL" << endl;
	}
	else
	{
		cout << "element not found." << endl;
	}



	// TASK7; #############################################################
	Tree<int> trSym;
	trSym.initTestTreeSym();
	if (IsSymetrical(trSym.getRoot()))
		cout << "is symetrical" << endl;
	else
		cout << "is not symetrical" << endl;



	// TASK8; #############################################################
	cout << endl;
	Tree<int> tr3;
	tr3.initTestTree();
	printTree(tr3.getRoot());
	FlipTreeHorizontally(tr3.getRoot());
	cout << "After horizontal flip: " << endl;
	printTree(tr3.getRoot());

	// TASK8; ##############################################################
	Node<int>* a = getNodeByTrace(tr.getRoot(), "rrll"); // 8
	Node<int>* b = getNodeByTrace(tr.getRoot(), "llr"); // 2
	
	PathFromToo(tr.getRoot(), a, b);
	cout << endl;
	
	// TASK9; ##############################################################
	Tree<char>* treeFromPrefix = BuildTreeFromPrefix("+/+523*43");

	cout << endl;
    return 0;
}

/*
// PREORDER DFS TRAVERSAL <ROOT> <LEFT> <RIGHT> 
void PreorderDFS(Node<int>* root)
{
	if (root == NULL)
		return;
	std::cout << root->data << " ";
	PreorderDFS(root->left);
	PreorderDFS(root->right);
}
*/