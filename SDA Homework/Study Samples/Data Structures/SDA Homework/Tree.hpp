/* 
	Tree Implementation using 3 Dynamic Arrays 
	Author: Ivo Yakov, FMI 61891
*/
#pragma once
#include "DArray.hpp"

enum Child
{
	left,
	right,
	none
};

template <typename T>
class Tree
{
private:
	DArray<T> a; // the value of the node at a[i]
	DArray<int> b; // the index in a of the left child of the node at a[i]
	DArray<int> c; // the index in a of the right child of the node at a[i]

	size_t lastIndex;
	size_t size;

	void RemoveSubtree(size_t index)
	{
		// If no element exists stop
		if (a[index] == NULL)
			return;

		// get the left and right children of element
		int lChildIndex = b[index];
		int rChildIndex = c[index];

		// delete the left and right children of element if they exist
		if (lChildIndex != -1)
			RemoveSubtree(lChildIndex);
		if (rChildIndex != -1)
			RemoveSubtree(rChildIndex);

		// delete the element and it's links to the children
		size--;
		a[index] = -1;
		b[index] = -1;
		c[index] = -1;
	}

public:
	
	// Constructor
	Tree()
	{
		a.Resize(15);
		a.FillWith(NULL);

		b.Resize(15);
		b.FillWith(-1);
		
		c.Resize(15);
		c.FillWith(-1);
		
		lastIndex = -1;
		size = 0;
	}
	
	Tree<T> operator=(Tree<T> other)
	{
		lastIndex = other.lastIndex;
		size = other.size;
		a = other.a;
		b = other.b;
		c = other.c;
		
		return *this;
	}

	// Add a Root to the tree
	// this method accepts 1 argument:
	// value       -> the value of the root element to be added
	void AddRoot(T value)
	{
		if (lastIndex == -1)
		{
			a.Insert(value, 0);
			lastIndex = 0;
			size = 1;
		}
		else throw std::exception("Tree already has a root");
	}

	// Add a Vertex (node) to the tree
	// this method accepts 3 arguments:
	// value       -> the value for the node to be added
	// parentIndex -> the index of the parent node to attach current value to
	// which       -> selection to attach this value to left or right of parent
	int Add(T value, int parentIndex, Child which)
	{
		// Only work if the tree is empty
		if (isEmpty())
			throw std::exception("Tree is empty, add a root");

		// Check if vertex already exists at that position
		if (which == Child::left && b[parentIndex] != -1)
			throw std::exception("Left Child already exists");
		if (which == Child::right && c[parentIndex] != -1)
			throw std::exception("Right Child already exists");
			
		// Create the vertex and store it's index
		int vindex = ++lastIndex;
		a.Insert(value, vindex);
		size++;

		// Set the parrent element's children to current vertex's index
		if (which == Child::left)
		{
			b[parentIndex] = vindex;
		}
		else if(which == Child::right)
		{
			c[parentIndex] = vindex;
		}

		return lastIndex;
	}
	
	// Find the index of the first matching element
	int GetIndex(T value)
	{
		// look for element
		for (int i = 0; i < a.Capacity(); i++) 
		{
			if (a[i] == value)
				return i;
		}
		
		//if element not found return -1
		return -1;
	}
	
	// Removes the left subtree from selected element
	void RemoveLeftSubtree(int index)
	{
		if (index < 0 && index >= b.Capacity())
			throw std::exception("Element outside array bounds");

		// If element doesn't have a left subtree
		if (b[index] == -1)
			throw std::exception("No element at this index");
		
		// Remove the link
		int lChildIndex = b[index];
		b[index] = -1;

		// Remove it's children recursively
		RemoveSubtree(lChildIndex);
	}

	// Removes the right subtree from selected element
	void RemoveRightSubtree(int index)
	{
		if (index < 0 && index >= b.Capacity())
			throw std::exception("Element outside array bounds");
		// If element doesn't have a left subtree
		if (c[index] == -1)
			throw std::exception("No element at this index");

		// Remove the link
		int rChildIndex = c[index];
		c[index] = -1;

		// Remove it's children recursively
		RemoveSubtree(rChildIndex);
	}
	
	int GetParentIndex(int childIndex)
	{
		if (childIndex < 0 || childIndex > a.Capacity())
			throw std::out_of_range("Invalid Index");

		// look for parent in b and c
		for (int i = 0; i < lastIndex; i++)
		{
			if (b[i] == childIndex)
				return i;
			if (c[i] == childIndex)
				return i;
		}

		return -1; // if no parent found return -1
	}

	int GetChildIndex(int parentIndex, Child which)
	{
		if (parentIndex < 0 || parentIndex > a.Capacity())
			throw std::out_of_range("Invalid Index");

		if (which == Child::left)
		{
			return b[parentIndex];
		}
		else if(which == Child::right)
		{
			return c[parentIndex];
		}
	}
	
	// get the value at given index
	T GetValueAtIndex(int index)
	{
		if (index < 0 || index >= a.Capacity())
			throw std::out_of_range("Invalid Index");

		if (a[index] != NULL)
			return a[index];
		else
			throw std::exception("No such index");
	}

	// Change the value at given index
	void SetValueAtIndex(int index, T value)
	{
		if (index < 0 || index >= a.Capacity())
			throw std::out_of_range("Invalid Index");

		a[index] = value;
	}

	// Return true if tree is empty 
	bool isEmpty()
	{
		return lastIndex == -1;
	}
	
	// Get the node count
	int Size()
	{
		return size;
	}

	// Print the array representation of the tree
	void PrintArr()
	{
		std::cout << "a: "; a.Print();
		std::cout << "b: "; b.Print();
		std::cout << "c: "; c.Print();
	}


};