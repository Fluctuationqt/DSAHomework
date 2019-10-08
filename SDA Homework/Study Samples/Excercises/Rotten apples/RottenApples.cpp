// RottenApples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LQueue.hpp"
#include <iostream>

class Pos
{
public:
	int x;
	int y;
	Pos(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}
};

void printQ(LQueue<Pos> q)
{
	int i = 0;
	while (!q.isEmpty())
	{
		Pos temp;
		q.pop(temp);
		std::cout << "q" << i << "(" << temp.x << "," << temp.y << ") ";
		i++;
	}
	std::cout << std::endl;
}

void printMatrix(int** a, int sizeX, int sizeY)
{
	//print the matrix
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			std::cout << a[y][x];
		}
		std::cout << std::endl;
	}
}

void placeApples(int** a)
{
	a[0][0] = 2;
	a[0][1] = 1;
	a[0][2] = 0;

	a[1][0] = 1;
	a[1][1] = 0;
	a[1][2] = 2;

	a[2][0] = 0;
	a[2][1] = 1;
	a[2][2] = 1;
}

bool inBounds(int val, int min, int max)
{
	if (val < max && val >= min)
		return true;
	else 
		return false;
}

// Look for new rotten apples in the array, that are to the left, right, top or down of 
// the current rotten apple that was popped from the queue.
// if a rotten apple is found push it at the back of the queue "q"
void FindNewRotten(Pos current, int** a, int sizeX, int sizeY, LQueue<Pos>& q)
{
	// when at valid element
	Pos check(current.x, current.y);

	//check to the right
	check.x++;
	if (inBounds(check.x, 0, sizeX) && a[check.y][check.x] == 1)
	{
		a[check.y][check.x] = 2;
		q.push(check);
	}

	//check to the left
	check.x -= 2;
	if (inBounds(check.x, 0, sizeX) && a[check.y][check.x] == 1)
	{
		a[check.y][check.x] = 2;
		q.push(check);
	}

	//check above
	check.x = current.x;
	check.y--;
	if (inBounds(check.y, 0, sizeY) && a[check.y][check.x] == 1)
	{
		a[check.y][check.x] = 2;
		q.push(check);
	}

	//check below
	check.y += 2;
	if (inBounds(check.y, 0, sizeY) && a[check.y][check.x] == 1)
	{
		a[check.y][check.x] = 2;
		q.push(check);
	}
}

int main()
{
	//initialize matrix 
	/* change the size here for larger matrix and then input apples in place apples! */
	const int sizeX = 3, sizeY = 3;
	int** a = new int*[sizeY];
	for (int i = 0; i < sizeY; i++)
		a[i] = new int[sizeX];

	//put apples in it
	placeApples(a);

	//print matrix
	std::cout << "### input matrix ###" << std::endl;
	printMatrix(a, sizeX, sizeY);

	// find first set of rotten apples and push them in the queue
	LQueue<Pos> q;
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			if (a[y][x] == 2)
			{
				q.push(Pos(x, y)); // push rotten apples
			}
		}
	}

	//Push delimiter to separate first step
	q.push(Pos(-1, -1));
	std::cout << "Queue: ";
	printQ(q);
	
	// Loop the queue of rotten apples until it's empty
	int ctr = 1;
	while (!q.isEmpty())
	{
		//view the front of the queue of rotten apple positions
		Pos current; 
		q.pop(current);

		// if at delimiter increment step counter and remove it
		if (current.x == -1 && current.y == -1)
		{
			// remove the delimiter
			q.pop(current);

			// print the matrix and queue
			std::cout << std::endl << "Step: " << ctr << std::endl;
			printMatrix(a, sizeX, sizeY);
			std::cout << "Queue: ";
			printQ(q);
			
			//if no more apples in the queue exit
			if (q.isEmpty())
			{
				break;
			}
			// else push another delimiter and increment the step counter
			q.push(Pos(-1, -1));
			ctr++;
		}
		else
		{
			// if not at delimiter, then we view around each rotten apple's position
			// and look for healthy apples. If we find one, it rots and we add it to the
			// queue to look for more around it on the next step
			FindNewRotten(current, a, sizeX, sizeY, q);
		}
	}
	
	std::cout << std::endl << "Time taken: " << ctr << std::endl;
	
    return 0;
}