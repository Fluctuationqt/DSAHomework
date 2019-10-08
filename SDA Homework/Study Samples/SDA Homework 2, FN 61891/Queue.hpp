#pragma once
using namespace std;

template <typename T>
class LQueue
{
private:
	size_t count;
	struct node
	{
		T data;
		node *next;
	} *front, *back;
	
	void deleteQueue()
	{
		T x;
		while (Pop(x));
		count = 0;
	}

	void copy(LQueue<T> const& sourceQueue)
	{
		back = front = NULL;
		count = sourceQueue.count;
		node *p = sourceQueue.front;
		while (p)
		{
			Push(p->data);
			p = p->next;
		}
	}
	
public:
	
	LQueue()
	{
		front = back = NULL;
		count = 0;
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

	void Push(T const &element)
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
		count++;
	}
	
	bool Pop(T &element)
	{	
		if (back == NULL)
			return false;
		node* p = front;
		if (front == back)
			front = back = NULL;
		else
			front = front->next;
		count--;
		element = p->data;
		delete p; // is the old front deleted here?
		return true;
	}

	// get the queue's head element
	bool Head(T & element) const
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

	// get the queue's tail element
	bool Tail(T & element) const
	{
		if (isEmpty())
		{
			return false;
		}
		else
		{
			element = back->data;
			return true;
		}
	}

	// return true if the queue is empty
	bool isEmpty() const
	{
		return back == NULL;
	}
	
	// returns the number of elements in queue
	size_t length()
	{
		return count;
	}
};