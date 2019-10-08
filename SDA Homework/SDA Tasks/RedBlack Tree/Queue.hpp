#pragma once
using namespace std;

template <typename T>
struct node
{
	T data;
	node *next;
};

template <typename T>
class LQueue
{
public:
	LQueue()
	{
		front = back = NULL;
		size = 0;
	}
	~LQueue()
	{
		deleteQueue();
	}
	LQueue(LQueue<T> const &sourceQueue)
	{
		copy(sourceQueue);
	}
	LQueue<T>& operator=(LQueue<T> const &sourceQueue)
	{
		if (this != &sourceQueue)
		{
			deleteQueue();
			copy(sourceQueue);
		}
		return *this;
	}

	void push(T const &element)
	{
		node<T>* temp = new node<T>;
		temp->data = element;
		temp->next = NULL;

		if (isEmpty())
			front = back = temp;
		else
		{
			back->next = temp;
			back = temp;
		}
		size++;
	}
	
	bool pop(T &element)
	{
		if (back == NULL)
			return false;
		node<T>* p = front;
		if (front == back)
			front = back = NULL;
		else
			front = front->next; // delete old front or lost pointer means just that?
		
		element = p->data;
		delete p;

		size--;
		return true;
	}

	bool head(T & element) const
	{
		if (isEmpty())
		{
			return false;
		}
		else
		{
			element = front->data;
			return true;
		}
	}
	
	int getSize()
	{
		return size;
	}

	bool isEmpty() const
	{
		return back == NULL;
	}
	
	void print()
	{
		T x;
		node<T>* p = front;
		while (p != NULL)
		{
			if (p->next == NULL)
				std::cout << p->data << " ";
			else
				std::cout << p->data << ", ";
			p = p->next;
		}
			
	}
private:
	node<T> *front, *back;
	int size;
	void deleteQueue()
	{
		T x;
		while (pop(x));
		size = 0;
	}

	void copy(LQueue<T> const& sourceQueue)
	{
		back = front = NULL;
		
		node<T> *p = sourceQueue.front;
		while (p)
		{
			push(p->data);
			p = p->next;
		}
		size = sourceQueue.size;
	}
};