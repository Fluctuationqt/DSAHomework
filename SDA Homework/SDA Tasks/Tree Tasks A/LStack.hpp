/* 
	Subject: Templated Linked Stack
	Author : Ivo Yakov, FMI 61891
*/
#pragma once

template <typename T>
class LStack
{
	struct node
	{
		T data;
		node* next;
	} * top;
	
	size_t size;

public:
	
	LStack()
	{
		top = nullptr;
	}

	LStack(LStack<T> const & other)
	{
		top = other.top;
		size = other.size;
	}

	LStack<T> & operator=(LStack<T> const & other)
	{
		top = other.top;
		size = other.size;
	}

	void Push(T const & element)
	{
		node * temp = new node;
		temp->data = element;
		if (top != nullptr)
		{
			temp->next = top;
		}
		else
		{
			temp->next = nullptr;
		}

		top = temp;
		size++;
	}
	
	T & Pop()
	{
		if (isEmpty())
			throw std::exception("Empty Stack. Cannot Pop()!");
		
		node * temp = top;
		
		if (top->next != nullptr)
		{
			top = top->next;
		}
		else
		{
			top = nullptr;
		}

		size--;
		return temp->data;
	}

	T & Top()
	{
		return top->data;
	}

	bool isEmpty()
	{
		return top == nullptr;
	}

	size_t Size()
	{
		return size;
	}
};