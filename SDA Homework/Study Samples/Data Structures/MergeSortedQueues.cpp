// DynamicStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Stack.hpp"
#include "Queue.hpp"
#include <sstream>
#include "windows.h"
// Q1: 2 3 5 10
// Q2: 1 4 6 
// res: 1 2 3 4 5 6 10

// ########## Text color setters #############
HANDLE hConsole;
void GetConsoleHandle()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Red()
{
	SetConsoleTextAttribute(hConsole, 12);
}

void Green()
{
	SetConsoleTextAttribute(hConsole, 10);
}

void Blue()
{
	SetConsoleTextAttribute(hConsole, 9);
}

void White()
{
	SetConsoleTextAttribute(hConsole, 7);
}

void ClearScreen(int pause)
{
	Sleep(pause);
	system("CLS");
}
// ##########################################

// Algorithm 1
LQueue<int> mergeSortedQueues(LQueue<int> Q1, LQueue<int>Q2)
{
	LQueue<int> Qres;
	int q1, q2;
	std::cout << "Q1_front, Q2_front" << std::endl << "-----------------"<<std::endl;
	while (!Q1.isEmpty() && !Q2.isEmpty())
	{
		Q1.head(q1);
		Q2.head(q2);
		std::cout << q1 << ", " << q2 << std::endl;

		if (q1 < q2)
		{
			Q1.pop(q1);
			std::cout << "pushing "<<q1<<" (first)";
			Qres.push(q1);

		}else if (q2 < q1)
		{
			Q2.pop(q2);
			std::cout << "pushing " << q2<<" (second)";
			Qres.push(q2);
		}
		else if (q2 == q1)
		{
			Q1.pop(q1);
			Qres.push(q1);

			Q2.pop(q2);
			Qres.push(q2);

			std::cout << "pushing " << q2 << " tow times (both)";
		}
		std::cout << std::endl;
		
	} 

	if (Q1.isEmpty() && !Q2.isEmpty())
	{
		std::cout << "first queue is empty pushing rest of second queue" << std::endl;
		while (Q2.pop(q2))
			Qres.push(q2);
	}
	else if (Q2.isEmpty() && !Q1.isEmpty())
	{
		std::cout << "second queue is empty pushing rest of first queue" << std::endl;
		while (Q1.pop(q1))
			Qres.push(q1);
	}
	std::cout << std::endl;
	return Qres;
}

// Algorithm 2
LQueue<int> makeUnique(LQueue<int> queue)
{
	LQueue<int> Qres;
	int t1, t2;
	while (!queue.isEmpty())
	{
		queue.pop(t1);
		bool hasNext = queue.head(t2);
		if (hasNext && t1 == t2)
			continue;
		Qres.push(t1);
	}
	return Qres;
}

// enter a queue from a line of numbers
void EnterQueue(LQueue<int> & queue)
{
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	int enterNumber;
	while (iss >> enterNumber)
		queue.push(enterNumber);
}

// enter both queues (UI)
void EnterQueues(LQueue<int> & Q1, LQueue<int> & Q2)
{
	// Queue 1
	Red();
	std::cout << "Enter sorted numbers(ex: 1 5 10 15):";
	EnterQueue(Q1);
	ClearScreen(0);
	White();
	std::cout << "Good!";
	ClearScreen(500);

	// Queue 2
	Green();
	std::cout << "Enter sorted numbers(ex: 2 4 15 20):";
	EnterQueue(Q2);
	ClearScreen(5);
	std::cout << "Sweet!";
	ClearScreen(500);
	White();
}

// print both queues(UI)
void PrintQueues(LQueue<int> & Q1, LQueue<int> & Q2)
{
	// Queue 1 
	Red();
	std::cout << "Q1 = [front| ";
	Q1.print();
	std::cout << "|back]" << std::endl;
	
	// Queue 2
	Green();
	std::cout << "Q2 = [front| ";
	Q2.print();
	std::cout << "|back]" << std::endl;

	// Empty Line
	std::cout << std::endl << std::endl;
	White();
}

int main()
{
	GetConsoleHandle();
	LQueue<int> Q1, Q2;
	EnterQueues(Q1, Q2);
	PrintQueues(Q1, Q2);
	
	LQueue<int> res = mergeSortedQueues(Q1, Q2);
	Blue();
	std::cout << "Result Queue 1: "; 
	res.print();
	std::cout << endl;
	
	
	LQueue<int> res2 = makeUnique(res);
	std::cout << "Result Queue 2: ";
	res2.print();
	std::cout << std::endl;
	
	White();
	system("pause");
    return 0;
}