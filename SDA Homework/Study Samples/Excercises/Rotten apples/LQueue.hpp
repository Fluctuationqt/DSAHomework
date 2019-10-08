#pragma once
using namespace std;

template <typename T>
class LQueue
{
private:

	struct node
	{
		T data;
		node *next;
	} *front, *back;

	void deleteQueue()
	{
		T x;
		while (pop(x));
	}

	void copy(LQueue<T> const& sourceQueue)
	{
		back = front = NULL;

		node *p = sourceQueue.front;
		while (p)
		{
			push(p->data);
			p = p->next;
		}
	}

public:

	LQueue()
	{
		front = back = NULL;
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
		node* temp = new node;
		temp->data = element;
		temp->next = NULL;

		if (isEmpty())
			front = back = temp;
		else
		{
			back->next = temp;
			back = temp;
		}
	}

	bool pop(T &element)
	{
		if (back == NULL)
			return false;
		node* p = front;
		if (front == back)
			front = back = NULL;
		else
			front = front->next;

		element = p->data;
		delete p; // is the old front deleted here?
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

	bool isEmpty() const
	{
		return back == NULL;
	}

	void print()
	{
		T x;
		node* p = front;
		while (p != NULL)
		{
			if (p->next == NULL)
				std::cout << p->data << " ";
			else
				std::cout << p->data << ", ";
			p = p->next;
		}
	}
};