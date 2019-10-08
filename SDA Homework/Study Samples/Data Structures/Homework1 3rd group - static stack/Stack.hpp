/*
	#################################################################
	Subject : An implementation of a template static array stack.
	Author  : Ivo Yakov, FN 61891, FMI Sofia.

	Implementation contains the following methods :
	Push(), Pop(), Clear(), isFull(), isEmpty(), Capacity() and Top().
	PS: Pop returns the popped value and Push doesn't return anything.
	##################################################################
*/

#pragma once

template<class T>
class Stack
{
private:
	T* m_data;     // Stack's container (pointer to static array).
	size_t m_size; // Stack's container size.
	size_t m_top;  // Stack's top element index.

	// Copy another stack. 
	// Used in Copy constructor and operator =
	void Copy(const Stack<T> &other)
	{
		if (other.isEmpty())
			return;

		// Copy other stack's parameters
		delete[] m_data;
		m_size = other.m_size;
		m_top = other.m_top;
		m_data = new T[m_size];

		// Copy each element from the other Stack
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i] = other.m_data[i];
		}
	}

public:

	// Default Constructor
	Stack(size_t size = 10)
	{
		m_size = size;
		m_data = new T[size];
		m_top = 0;
	}

	// Copy Constructor
	Stack(const Stack<T> &other)
	{
		//m_data = nullptr;
		Copy(other);
	}

	// Operator '=' definition
	const Stack<T> Stack<T>::operator=(const Stack<T> &other)
	{
		if (this != &other)
		{
			Copy(other);
		}
		return *this;
	}

	// Destructor
	~Stack()
	{
		m_top = 0;
		m_size = 0;
		delete[] m_data;
	}

	// Adds elements to the stack's top
	void Push(const T& element)
	{
		if (!isFull())
			m_data[m_top++] = element;
		else
			throw std::exception("Cannot Push(). Stack is full.");
	}

	//  Returns elements from the stack's top 
	//  returned elements get removed from Stack
	T& Pop()
	{
		if (!isEmpty())
			return m_data[--m_top];
		else
			throw std::exception("Cannot Pop(). Stack is empty");
	}

	// Clears the stack's data
	void Clear()
	{
		delete[] m_data;
		m_top = 0;
		m_data = new T[m_size];
	}

	// Returns true if the stack is full
	bool isFull()
	{
		return m_top == m_size;
	}

	// Returns true if the stack is empty
	bool isEmpty()
	{
		return m_top == 0;
	}

	// Returns the maximum size of the stack
	size_t Capacity()
	{
		return m_size;
	}

	// Returns the top element of the stack, without removing it
	T& Top()
	{
		if(!isEmpty())
			return m_data[m_top - 1];
		else
			throw std::exception("Cannot View Top. Stack is empty");
	}
};