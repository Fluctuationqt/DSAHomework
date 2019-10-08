#include "Queue.hpp"
#include <string>
enum Color{ Red, Black };
enum ChildType{ LeftChild, RightChild, NoChild};

template<typename T>
struct Node
{
	Color color;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	T data;
};

template<typename T>
class Tree
{
private:
	Node<T>* root;
	Node<T>* sentinel;
	int GetDepthReccursive(Node<T>* root);
	void FindPositionAndAdd(Node<T>* root, Node<T>* element);
	void FindPositionAndRemove(Node<T>* root, Node<T>* element);
	ChildType GetChildType(Node<T>* node);
	void LeftRotation(Node<T>* node);
	void RightRotation(Node<T>* node);
public:
	Tree();
	Node<T>* GetRoot();
	int GetHeight();
	void Add(T element);
	void Remove(T element);
	void Print();

};

template<typename T>
Tree<T>::Tree()
{
	sentinel = new Node<T>{ Black, nullptr, nullptr, nullptr, NULL };
	root = sentinel;
}

template<typename T>
Node<T>* Tree<T>::GetRoot()
{
	return root;
}

template<typename T>
int Tree<T>::GetDepthReccursive(Node<T>* root)
{
	if (root == sentinel)
		return 0;

	int leftDepth = GetDepthReccursive(root->left);
	int rightDepth = GetDepthReccursive(root->right);

	if (leftDepth > rightDepth)
		return leftDepth + 1;
	else
		return rightDepth + 1;
}

template<typename T>
ChildType Tree<T>::GetChildType(Node<T>* node)
{
	if (node->parent->left == node)
		return LeftChild;
	else if (node->parent->right == node)
		return RightChild;
	else
		return NoChild;
}

template<typename T>
int Tree<T>::GetHeight()
{
	return GetDepthReccursive(root);
}

template<typename T>
void Tree<T>::LeftRotation(Node<T>* node)
{
	Node<T>* rightChild = node->right;
	
	rightChild->parent = node->parent;
	ChildType nodeType = GetChildType(node);
	if (nodeType == NoChild)
		root = rightChild;
	else if(nodeType == LeftChild)
		node->parent->left = rightChild;
	else if (nodeType == RightChild)
		node->parent->right = rightChild;
	
	node->right = rightChild->left;
	if (rightChild->left != sentinel)
	{
		rightChild->left->parent = node;
	}
	rightChild->left = node;
	node->parent = rightChild;

}

template<typename T>
void Tree<T>::RightRotation(Node<T>* node)
{
	Node<T>* leftChild = node->left;

	leftChild->parent = node->parent;
	ChildType nodeType = GetChildType(node);
	if (nodeType == NoChild)
		root = leftChild;
	else if (nodeType == LeftChild)
		node->parent->left = leftChild;
	else if (nodeType == RightChild)
		node->parent->right = leftChild;

	node->left = leftChild->right;
	if (leftChild->right != sentinel)
	{
		leftChild->right->parent = node;
	}

	leftChild->right = node;
	node->parent = leftChild;
}

template<typename T>
void Tree<T>::FindPositionAndAdd(Node<T>* root, Node<T>* element)
{
	if (element->data < root->data)
	{
		if (root->left == sentinel)
		{
			root->left = element;
			element->parent = root;
		}
		else
			FindPositionAndAdd(root->left, element);
	}
	else if (element->data > root->data)
	{
		if (root->right == sentinel)
		{
			root->right = element;
			element->parent = root;
		}
		else
			FindPositionAndAdd(root->right, element);
	}
	else throw std::exception("Element already exists in tree");
}

template<typename T>
void Tree<T>::Add(T element)
{ 
	// CREATE AND ADD ELEMENT
	Node<T>* CreatedNode = new Node<T>{ Red, sentinel, sentinel, sentinel, element };
	if (root == sentinel)
	{
		root = CreatedNode;
	}
	else
	{
		FindPositionAndAdd(root, CreatedNode);
	}

	// FIX BALANCE
	Node<T>* newNode = CreatedNode;
	if (newNode->parent)
	{
		// if parent is red
		while(newNode->parent->color == Red)
		{
			// if parent is left child
			if (GetChildType(newNode->parent) == LeftChild)
			{
				Node<T>* uncle = newNode->parent->parent->right;
				
				if (uncle->color == Red)
				{
					newNode->parent->color = Black;
					uncle->color = Black; // to fix the property of equal blacks in each subtree
					uncle->parent->color = Red; // again fix equality of blacks
					newNode = uncle->parent;
				}
				else if (uncle->color == Black)
				{
					if (GetChildType(newNode) == RightChild)
					{
						newNode = newNode->parent;
						LeftRotation(newNode);
					}
					newNode->parent->color = Black;
					newNode->parent->parent->color = Red;
					RightRotation(newNode->parent->parent);
				}
			}
			// if parent is right child
			else if(GetChildType(newNode->parent) == RightChild)
			{
				Node<T>* uncle = newNode->parent->parent->left;

				if (uncle->color == Red)
				{
					newNode->parent->color = Black;
					uncle->color = Black; // to fix the property of equal blacks in each subtree
					uncle->parent->color = Red; // again fix equality of blacks
					newNode = uncle->parent;
				}
				else if (uncle->color == Black)
				{
					if (GetChildType(newNode) == LeftChild)
					{
						newNode = newNode->parent;
						RightRotation(newNode);
					}
					newNode->parent->color = Black;
					newNode->parent->parent->color = Red;
					LeftRotation(newNode->parent->parent);
				}
			}
		}
	}

	root->color = Black;
}

template<typename T>
void Tree<T>::FindPositionAndRemove(Node<T>* current, Node<T>* element)
{
	if (current == element)
	{
		ChildType currentType = GetChildType(current);
		if (current->parent == sentinel) // if current is the tree root
		{
			root = sentinel;
			return;
		}

		if(current->right == sentinel && current->left == sentinel) // current has no children
		{
			if (currentType == LeftChild)
				current->parent->left = sentinel;
			else if (currentType == RightChild)
				current->parent->right = sentinel;
		}
		else if (current->right == sentinel && current->left != sentinel) // current has only left child
		{
			current->left->parent = current->parent;
			if (currentType == RightChild)
			{
				current->parent->right = current->left;
			}
			else if (currentType == LeftChild)
			{
				current->parent->left = current->left;
			}
		}
		else if (current->left == sentinel && current->right != sentinel) // current has only right child
		{
			current->right->parent = current->parent;
			if (currentType == RightChild)
			{
				current->parent->right = current->right;
			}
			else if (currentType == LeftChild)
			{
				current->parent->left = current->right;
			}
		}
		else // current has two children
		{
			Node<T>* successor = current->right;
			while (successor->left != sentinel)
			{
				successor = successor->left;
			}
			current->data = successor->data;
			successor = sentinel;
		}
		
	}

	if(element->data < root->data)
		FindPositionAndRemove(root->left, element);
	else
		FindPositionAndRemove(root->right, element);
}

template<typename T>
void Tree<T>::Print()
{
	LQueue<Node<T>*> queue;
	Node<T>* current;
	queue.push(root);
	queue.push(nullptr);
	int level = 0;
	int height = GetHeight();
	
	while (queue.pop(current))
	{
		if (queue.getSize() == 0)
			break;

		if (current == nullptr)
		{
			cout << endl;
			queue.push(nullptr);
		}
		else
		{
			if (current->color == Red)
				cout << current->data << ", Red :{ ";
			else
				cout << current->data << ", Black :{";

			if (current->left != sentinel)
			{
				cout << current->left->data;
				queue.push(current->left);
			}
			else
			{
				cout << "NULL";
			}
			cout << ", ";
			if (current->right != sentinel)
			{
				cout << current->right->data;
				queue.push(current->right);
			}
			else
			{
				cout << "NULL";
			}
			cout << " } " << endl;
		}
	}
}
