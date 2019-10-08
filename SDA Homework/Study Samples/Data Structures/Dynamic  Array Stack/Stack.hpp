#pragma once
/* 
	Subject : Dynamic Array Stack Implementation
	Author  : Ivo Yakov, FMI 61891
*/
template <typename T>
class Stack
{
private:
	T* m_data;		   // pointer stack's data dynamic array
	size_t m_capacity; // stack's maximum capacity
	size_t m_top;      // stack's top element index

	// resizes the stack's parameters and dynamic array
	void Stack::Resize()
	{
		T* temp = m_data;
		m_data = new T[m_capacity * 2];
		m_capacity *= 2;
		CopyArray(temp);
		/*FOR TESTING std::cout << "Resized stack to " << m_capacity << std::endl; */
	}

	// copies a stack
	void CopyStack(Stack<T> const& other)
	{
		delete[] m_data;
		m_capacity = other.m_capacity;
		m_data = new T[m_capacity];
		m_top = other.m_top;
		CopyArray(other.m_data);
	}

	// copies a stack's dynamic array
	void CopyArray(T const* otherData)
	{
		for (size_t i = 0; i < m_capacity; i++)
			m_data[i] = otherData[i];
	}

	// returns true if stack is at full capacity
	bool isFull()
	{
		return m_top == m_capacity;
	}

public:
	// default constructor
	Stack(size_t initialCapacity = 2)
	{
		m_data = new T[initialCapacity];
		m_capacity = initialCapacity;
		m_top = 0;
	}

	// copy constructor
	Stack(Stack<T> const& other)
	{
		CopyStack(other);
	}

	// operator = definition
	Stack<T> operator=(Stack<T> other)
	{
		CopyStack(other);
	}

	// destructor
	~Stack()
	{
		delete[] m_data;
	}

	// Push element to stack's top
	void Push(T const& element)// ?
	{
		if (isFull())
			Resize();
		m_data[m_top++] = element;
		/*FOR TESTING std::cout << "Pushed data:" << element << std::endl; */
	}

	// Pop element from stack's top (returns a T element)
	T& Pop() // or T Pop()
	{
		if (isEmpty())
			throw std::exception("Stack is empty. Cannot Pop()");
		return m_data[--m_top];
	}

	// View the stack's top element (returns a T element)
	T Top()
	{
		if (isEmpty())
			throw std::exception("Stack is empty. Cannot get Top()");
		return m_data[m_top-1];
	}

	// returns true if stack is empty
	bool isEmpty()
	{
		return m_top == 0;
	}

	/* FOR TESTING
	// prints the stack's elements if they are a primitive data type
	void Print()
	{
		std::cout << "Stack :";
		for (int i = 0; i < m_top; i++)
			std::cout << m_data[i] << " ";
		std::cout << std::endl;
	}
	*/
};