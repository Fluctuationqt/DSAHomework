/*
	Example Usage of Tree and TreeFactory
	Author: Ivo Yakov, FMI 61891
*/
#include "stdafx.h"
#include <iostream>
#include "DArray.hpp" 
#include "Tree.hpp"
#include "TreeFactory.hpp"

Tree<int> & CreateTestTree()
{
	Tree<int> * tree = new Tree<int>();
	
	tree->AddRoot(1);
	tree->Add(2, tree->GetIndex(1), Child::left);
	tree->Add(3, tree->GetIndex(2), Child::left);
	tree->Add(4, tree->GetIndex(3), Child::left);
	tree->Add(5, tree->GetIndex(2), Child::right);
	tree->Add(6, tree->GetIndex(1), Child::right);
	tree->Add(7, tree->GetIndex(6), Child::left);
	return *tree;
}

void ExampleC()
{
	Tree<int> a;
	a.AddRoot(1);
	a.Add(2, a.GetIndex(1), Child::left);
	a.Add(3, a.GetIndex(2), Child::left);
	a.Add(4, a.GetIndex(3), Child::left);
	a.Add(5, a.GetIndex(2), Child::right);
	a.Add(6, a.GetIndex(1), Child::right);
	a.Add(7, a.GetIndex(6), Child::left);
	std::cout<<a.Add(9, a.GetIndex(3), Child::right)<<std::endl;
	
	std::cout <<"parentIndex of 4 " << a.GetParentIndex(a.GetIndex(4)) << std::endl;
	std::cout << "parent of 4 is " << a.GetValueAtIndex(a.GetParentIndex(a.GetIndex(4))) << std::endl;

	std::cout << a.Size() << std::endl;
	a.RemoveLeftSubtree(a.GetIndex(2));
	std::cout << a.Size() << std::endl;
	a.RemoveLeftSubtree(a.GetIndex(1));
	std::cout << a.Size() << std::endl;
	a.RemoveRightSubtree(a.GetIndex(1));
	std::cout << a.Size() << std::endl;
	a.PrintArr();
}

void ExampleB()
{
	try
	{
		Tree<char> a;
		//level 0
		a.AddRoot('a');
		
		//level 1
		a.Add('b', a.GetIndex('a'), Child::left);
		a.Add('c', a.GetIndex('a'), Child::right);

		//level 2
		a.Add('d', a.GetIndex('b'), Child::left);
		a.Add('e', a.GetIndex('b'), Child::right);

		a.Add('f', a.GetIndex('c'), Child::left);
		a.Add('g', a.GetIndex('c'), Child::right);

		//level 3
		a.Add('h', a.GetIndex('f'), Child::left);
		a.PrintArr();
		std::cout << "the parent of f is " << a.GetValueAtIndex(a.GetParentIndex(a.GetIndex('f'))) << std::endl; // c -> f
		std::cout << "the child of f is " << a.GetValueAtIndex(a.GetChildIndex(a.GetIndex('f'), Child::left)) << std::endl;
		a.PrintArr();
		a.RemoveLeftSubtree(a.GetIndex('a'));
		a.PrintArr();
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void ExampleA()
{
	TreeFactory treeBuilder;
	Tree<int> tree;
	try
	{
		//tree = treeBuilder.CreateTree<int>();
		//tree.PrintArr();

		tree = CreateTestTree();
		tree.PrintArr();
		std::cout << std::endl;
		std::cout << "index of element 3 is " << tree.GetIndex(3) << std::endl;
		std::cout << "parent of 3 is " << tree.GetValueAtIndex(tree.GetParentIndex(tree.GetIndex(3))) << std::endl;

		// get the index of the left child of node at index 2
		int temp = tree.GetChildIndex(2, Child::left);

		// get that child's value
		std::cout << "child of element at index 2 is " << tree.GetValueAtIndex(temp) << std::endl;
		
		tree.PrintArr();
		std::cout << std::endl;
		tree.RemoveLeftSubtree(tree.GetIndex(2)); //remove left subtree of node 2
		tree.PrintArr();
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

}

int main()
{

	/* Some Usage Examples */
	ExampleA();
	std::cout << std::endl;
	ExampleB();
	std::cout << std::endl;
	ExampleC();
	
	/* Create A Tree from console input Example */
	try 
	{
		Tree<int> tr;
		TreeFactory trf;
		tr = trf.CreateTree<int>();
		tr.PrintArr();
	}
	catch (std::exception ex) { std::cout << ex.what() << std::endl; }
	return 0;
}