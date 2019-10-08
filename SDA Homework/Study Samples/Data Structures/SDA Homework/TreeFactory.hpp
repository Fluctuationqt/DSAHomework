/*
	Tree Factory Creates a Tree from console input
	Author: Ivo Yakov, FMI 61891
*/
#pragma once
class TreeFactory
{
public:
	template <typename T>
	Tree<T> & CreateTree()
	{
		Tree<T> * tr = new Tree<T>();
		T value;
		std::cout << "Root: ";
		std::cin >> value;
		tr->AddRoot(value);

		char c;
		std::cout << "Add left tree of: " << value << ", y/n? ";
		std::cin >> c;


		if (c == 'y')
			CreateSubtree(tr, 0, Child::left);

		std::cout << "Add right tree of: " << value << ", y/n? ";
		std::cin >> c;

		if (c == 'y')
			CreateSubtree(tr, 0, Child::right);

		return *tr;
	}

private:
	template <typename T>
	void CreateSubtree(Tree<T> * tr, int index, Child which)
	{
		T value;
		std::cout << "Root: ";
		std::cin >> value;
		int idx = tr->Add(value, index, which);

		char c;
		std::cout << "Add left tree of: " << value << ", y/n? ";
		std::cin >> c;
		if (c == 'y')
			CreateSubtree(tr, idx, Child::left);

		std::cout << "Add right tree of: " << value << ", y/n? ";
		std::cin >> c;
		if (c == 'y')
			CreateSubtree(tr, idx, Child::right);
	}

};