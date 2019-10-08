// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Queue.hpp"
#include <iostream>
#include <string>
#include "LStack.hpp"


// Print Queue of integers
void PrintQ(LQueue<int> q)
{
	std::cout << "front| ";
	while (!q.isEmpty())
	{
		int temp;
		q.Pop(temp);
		std::cout << temp << " ";
	}
	std::cout << "|back" << std::endl;
}

// Print Queue of Queues of integers
void PrintQQ(LQueue<LQueue<int>> qq)
{
	LQueue<int> q;

	std::cout << "##### Queue of Queues #####" << std::endl;
	std::cout << ">     [HEAD]" << std::endl;

	while (qq.Pop(q))
	{
		PrintQ(q);
	}

	std::cout << ">     [TAIL]" << std::endl;
	std::cout << "###########################" << std::endl << std::endl;
}

// UI comments and shit
void PrintUI(LQueue<int> & inputQ, int ctr)
{
	std::cout << "Current Queue: ";
	PrintQ(inputQ);
	std::cout << std::endl;
	std::cout << "Input only increasing numbers!" << std::endl;
	std::cout << "Return, Any non-numeric symbol OR non-increasing number will stop the input";
	std::cout << std::endl << "Queue[" << ctr << "] = ";
}

// Clear the screen
void ClearConsole()
{
	system("CLS");
}

// inputs queue of integers that are in increasing order
LQueue<int> Input()
{
	LQueue<int> inputQ;

	int max     = INT_MIN;
	int current = INT_MIN;
	int prev    = INT_MIN;
	int ctr = 0;

	do 
	{
		// User Interface for Input();
		PrintUI(inputQ, ctr);
		
		// Get input
		string input;
		std::getline(std::cin, input);
		
		// If number convert it else stop
		try 
		{
			current = std::stoi(input);
		}
		catch (std::exception ex)
		{
			break;
		}

		// if the current is bigger than max push it
		// else stop
		if (current >= max)
		{
			inputQ.Push(current);
			inputQ.Tail(prev);
			ctr++;
		}
		else
		{
			break;
		}
		// Set max to current if current is largest
		if (max < current)
		{
			max = current;
		}

		ClearConsole();
	} while (prev >= max);
	ClearConsole();

	return inputQ;
}

// reverses the FIFO order
template <typename T>
void ReverseStack(LStack<T> &Stack)
{
	LQueue<T> queue;
	while (!Stack.isEmpty())
	{
		queue.Push(Stack.Pop());
	}

	while (!queue.isEmpty())
	{
		T temp;
		queue.Pop(temp);
		Stack.Push(temp);
	}
}

// pops all elements from fromStack and pushes them to toStack
template <typename T>
void PushStack(LStack<T> & fromStack, LStack<T> & toStack)
{
	while (!fromStack.isEmpty())
	{
		toStack.Push(fromStack.Pop());
	}
}

// pop the elements of a stack and push them to a queue
// then return a pointer to that queue
template <typename T>
LQueue<T> * StackToQueue(LStack<T> & fromStack)
{
	LQueue<T> * queue = new LQueue<T>();
	while (!fromStack.isEmpty())
	{
		queue->Push(fromStack.Pop());
	}

	return queue;
}

// Sorts the numbers in a queue of queues of integets and prints them in a line
// sorted from largest to smallest
LQueue<int> GetNumbers(LQueue<LQueue<int>> queue_of_queues)
{
	LQueue<int> q;
	LStack<int> result;

	// loop through the superqueue while it still has subqueues
	while (!queue_of_queues.isEmpty())
	{
		//get each subqueue
		if (queue_of_queues.Pop(q))
		{
			int current;
			if (q.Pop(current)) // view current subqueue front element
			{
				LStack<int> tempBuffer;
				
				// if there still are numbers in the result stack
				if (!result.isEmpty())
				{
					// while the top of those numbers is bigger than
					// the current subqueue's front element 
					while (current < result.Top())
					{
						// push the numbers from the top of the result
						// stack in a buffer stack
						tempBuffer.Push(result.Pop());
					}
				}

				// if we've reached a top number in the result stack
				// that is less than or equal to our current subqueue front
				// number, push the current subqueue's front number
				// in the result stack and then push the buffer stack
				// back into our result stack
				result.Push(current);
				PushStack(tempBuffer, result);	
			}
		}

		// put subqueue back in superqueue if the subqueue
		// still has numbers in it (here we remove the empty queues)
		if (!q.isEmpty())
			queue_of_queues.Push(q); 
	}

	// flip the numbers in the result stack so that the
	//  numbers in it are back in increasing order
	ReverseStack(result);

	// convert the result stack to a queue and return it
	return *StackToQueue(result);
}

int main()
{
	LQueue<LQueue<int>> queue_of_queues;
	LQueue<int> queue;

	// loop while there are queues coming from user input
	do 
	{
		queue = Input(); 
		if (!queue.isEmpty())
		{
			queue_of_queues.Push(queue);
		}
	} while (!queue.isEmpty());
	
	// for UI purpose visually show superqueue
	PrintQQ(queue_of_queues); 

	// print the increasing numbers from the superqueue
	queue = GetNumbers(queue_of_queues);
	
	std::cout << "Result Queue: ";
	// print the result
	PrintQ(queue);
    
	return 0;
}