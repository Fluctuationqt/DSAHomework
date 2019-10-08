#pragma once

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
};

template<typename T>
class CList
{
	int size;
	Node<T>* current;
	Node<T>* end;
public:
	CList()
	{
		current = end = nullptr;
		size = 0;
	}
	
	bool isEmpty()
	{
		return (end == nullptr);
	}

	void toEnd(T const & element)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = element;
		if (isEmpty())
		{
			newNode->next = newNode;
			end = newNode;
			current = newNode;
		}
		else 
		{
			newNode->next = end->next;
			end->next = newNode;
			end = newNode;
		}
		size++;
	}

	void ResetIterator()
	{
		current = end->next;
	}

	Node<T>* Iterate()
	{
		Node<T>* result = current;
		current = current->next;
		return result;
	}

	Node<T>* End()
	{
		return end;
	}

	int Size()
	{
		return size;
	}
};