#pragma once

template <typename T>
class DArray
{
private:
	T* a;
	size_t size;

public:
	DArray()
	{
		size = 5;
		a = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			a[i] = NULL; // NULL Fill
		}
	}
	
	DArray(size_t initSize)
	{
		size = initSize;
		a = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			a[i] = NULL; // NULL Fill
		}
	}
	
	~DArray()
	{
		delete[] a;
	}

	// Copy constructor
	DArray(DArray& other)
	{
		size = other.size;
		a = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			a[i] = other[i]; // NULL Fill
		}
	}

	// Operator = definition
	DArray<T> operator=(DArray<T> other)
	{
		size = other.size;
		a = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			a[i] = other[i]; // NULL Fill
		}
		return *this;
	}

	// Resizes the array to newSize, current elements persist
	void Resize(size_t newSize)
	{
		T *temp;
		temp = new T[newSize];
		size_t i = 0;
		for (i; i < size; i++)
		{
			temp[i] = a[i];// copy old
		}
		for (i; i < newSize; i++)
		{
			temp[i] = NULL; // NULL fill rest
		}

		delete[] a;
		a = temp;
		size = newSize;
	}

	// Get the capacity
	size_t Capacity()
	{
		return size;
	}

	/*
		Insert element at position
		resizes the array to 2*pos if position is outside capacity
	*/
	void Insert(T x, size_t pos)
	{
		if (size <= pos)
		{
			Resize(pos * 2);
			a[pos] = x;
		}
		else if (pos < 0)
		{
			throw std::out_of_range("Index out of range");
		}
		else
		{
			a[pos] = x;
		}
	}

	/*
		Get value at position, returns a copy of the value
		if pos is outside capacity throws an out of range exception
	*/
	T Get(size_t pos)
	{
		if (size <= pos || pos < 0)
		{
			throw std::out_of_range("Index out of range");
		}
		else
		{
			return a[pos];
		}
	}

	/*  
		Operator[] Mutator, only works in range of 0 to Capacity!
		When [pos] is outside capacity or less than 0 
		it throws an out of range exception
	*/
	T& operator[] (size_t pos) {
		if (pos < 0 || size <= pos)
		{
			throw std::out_of_range("Index out of range");
		}
		else
		{
			return a[pos];
		}
	}

	// Fill entire array with the same thing
	void FillWith(T data)
	{
		for (size_t i=0; i < size; i++)
		{
			a[i] = data;
		}
	}

	// only prints array of primitive types or types with redefined operator<<
	void Print()
	{
		for (size_t i = 0; i < size; i++)
		{
			if(a[i]!=NULL)
				std::cout << a[i] << ", ";
		}
		std::cout << std::endl;
	}
};