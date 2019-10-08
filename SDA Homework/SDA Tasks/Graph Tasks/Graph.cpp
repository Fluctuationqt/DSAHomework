// Graph.cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"
#include <string>
#include <fstream>
#include "LStack.hpp"
#include "Queue.hpp"
#include <unordered_set>
using namespace std;

template<typename T>
void AddIfDoesntExist(T v, DirGraph<T> & g)
{
	// check if current vertex exists in graph, else create it
	if (!g.hasVertex(v))
	{
		g.addVertex(v);
	}
}


void CreateNodeFromStringOfIntegers(string line, DirGraph<int> & g)
{

	list<int> vertices;

	istringstream iss(line);
	string word;
	while (iss >> word)
	{
		vertices.push_back(std::stoi(word));
	}

	// get the front of vertices and store it as current vertex
	int CurrentVertex = vertices.front();
	vertices.pop_front();

	AddIfDoesntExist<int>(CurrentVertex, g);


	// loop vertices that current is connected to
	for (auto& nextVertex : vertices)
	{
		AddIfDoesntExist<int>(nextVertex, g);
		g.addEdge(CurrentVertex, nextVertex);
	}
}

void CreateNodeFromStringOfStrings(string line, DirGraph<string> & g)
{

	list<string> vertices; // contains all vertices from line

	// read line word by word (skipping spaces)
	istringstream iss(line);
	string word;
	while (iss >> word)
	{
		vertices.push_back(word); // push each vertex from line insde vertices
	}

	// get the front of vertices and store it as current vertex and remove it from vertices. It will be the created vertex
	string CurrentVertex = vertices.front();
	vertices.pop_front();
	// from now on vertices contains the relations that CurrentVertex is connected to.

	AddIfDoesntExist<string>(CurrentVertex, g); // create the Current Vertex if it doesn't exist


	// loop vertices that current is connected to and add them to it as edges
	for (auto& nextVertex : vertices)
	{
		AddIfDoesntExist<string>(nextVertex, g); // if they don't exist create them.
		g.addEdge(CurrentVertex, nextVertex);
	}
}

void FileOfIntegersToGraph(string fileName, DirGraph<int> & g)
{
	ifstream infile(fileName);
	std::string line;
	while (std::getline(infile, line))
	{
		CreateNodeFromStringOfIntegers(line, g);
	}
}

void FileOfStringsToGraph(string fileName, DirGraph<string> & g)
{
	ifstream infile(fileName);
	std::string line;
	while (std::getline(infile, line))
	{
		CreateNodeFromStringOfStrings(line, g);
	}
}

void Task1()
{
	DirGraph<int> g;
	FileOfIntegersToGraph("Graph.txt", g);
	g.print();
	cout << endl << endl;
	g.removeVertex(150);
	g.removeVertex(0);
	cout << "has3:" << g.hasEdge(3, 2) << endl;
	g.print();
}

bool lookForWordInGraph(string word, DirGraph<string> & g)
{
	for (int i = 0; i < word.length() - 1; i++)
	{
		string from = string(1, word[i]);
		string to = string(1, word[i + 1]);

		if (!g.hasEdge(from, to))
			return false;
	}
	return true;
}

void Task2()
{
	DirGraph<string> g;

	FileOfStringsToGraph("Graph2.txt", g);
	g.print();
	cout << "has word" << lookForWordInGraph("abababde", g) << endl;

	cout << endl << endl;
}

template<typename T>
DirGraph<T>* ReverseGraph(DirGraph<T>& g)
{
	DirGraph<T>* rg = new DirGraph<T>();
	list<T> vertices = g.getVetices();
	for (auto& vertex : vertices)
	{
		list<T>* rels = g.getVertexRels(vertex);
		for (auto& rel : (*rels))
		{
			if (rel != vertex)
			{
				string ReverseNode = rel + " " + vertex;
				CreateNodeFromStringOfStrings(ReverseNode, *rg);
			}
		}

	}

	return rg;
}

template<typename T>
bool FindInQueue(T wanted, LQueue<T> q)
{
	T el;
	int i = 0;
	while (q.pop(el))
	{
		if (el == wanted)
		{
			q.push(el);
			return true;
		}
		else
			q.push(el);

		if (i == q.getSize())
		{
			q.push(el);
			return false;
		}
		i++;
	}
	return false;
}

void FindAllPathsFromNode(string from,
	string to,
	int maxLength,
	int depthCounter,
	DirGraph<string> & g,
	LQueue<string> visited,
	LQueue<string> excluded)
{
	cout << "Searching for path: " << endl;
	if (from == to)
	{
		cout << "Path Found:";
		string last;

		while (visited.pop(last))
		{
			cout << last << " ";
		}
		cout << to << ", with length: " << depthCounter << endl;
		return;

	}

	list<string>* rels = g.getVertexRels(from);
	visited.push(from);
	for (auto& rel : (*rels))
	{
		if (rel != from && !FindInQueue(rel, visited) && !FindInQueue(rel, excluded) && maxLength > depthCounter)
		{
			FindAllPathsFromNode(rel, to, maxLength, depthCounter + 1, g, visited, excluded);
		}
	}

}


template<typename T>
bool isCyclic(DirGraph<T>& g)
{

	LQueue<T> allVisited; // the nodes here have been checked for cycles, they are sent as refference
	LQueue<T> temp; // only used in recursion
	for (auto& vertex : g.getVetices())
	{
		// check if vertex has been visited
		if (!FindInQueue(vertex, allVisited))
		{
			// check if vertex has a tree
			if (CheckForCycles(vertex, g, temp, allVisited))
			{
				return true;
			}
		}
	}
	return false;
}

template<typename T>
bool CheckForCycles(T from, DirGraph<T>& g, LQueue<T> visited, LQueue<T>& allVisited)
{
	list<T>* rels = g.getVertexRels(from);
	visited.push(from); // this queue gets reset after each Reccursion ends for a node from
	allVisited.push(from); // this queue doesn't reset at all.Just keep pushing every visited node in the queue
	// for each vertexrel
	for (auto& rel : (*rels))
	{
		if (rel != from) // skip first in vertexrels (it is equal to from)
		{
			// here for each rel of from check if the rel is visited or check if it's tree has a loop
			if (FindInQueue(rel, visited) || CheckForCycles(rel, g, visited, allVisited))
				return true;
		}
	}
	// allVisited.push(from); can be here too without any problems
	return false;
}


template<typename T>
void FillTopologicalStack(T from, DirGraph<T>& g, LQueue<T> visited, unordered_set<T>& allVisited, LStack<T> & tStack)
{
	list<T>* rels = g.getVertexRels(from);
	visited.push(from); // this queue gets reset after each Reccursion ends for a node from

						   // for each vertexrel
	for (auto& rel : (*rels))
	{
		if (rel != from) // skip first in vertexrels (it is equal to from)
		{
			// here for each rel of from check if the rel is visited or check if it's tree has a loop
			if (!FindInQueue(rel, visited))
			{
				FillTopologicalStack(rel, g, visited, allVisited, tStack);
			}

		}
	}
	if (allVisited.find(from) == allVisited.end())
	{
		tStack.Push(from);
		allVisited.insert(from); // this queue doesn't reset at all.Just keep pushing every visited node in the queue
	}
	return;
}

template<typename T>
void PrintTopological(DirGraph<T>& g)
{
	LStack<T> TopologicalStack;
	unordered_set<T> allVisited; // the nodes here have been checked for cycles, they are sent as refference
	LQueue<T> temp; // only used in recursion
	for (auto& vertex : g.getVetices())
	{
		// check if vertex has been visited
		if (allVisited.find(vertex) == allVisited.end())
		{
			FillTopologicalStack(vertex, g, temp, allVisited, TopologicalStack);
		}
	}
	while (!TopologicalStack.isEmpty())
	{
		cout << TopologicalStack.Pop() << " ";
	}
	cout << endl;
}

void Task3()
{
	DirGraph<string> g;
	FileOfStringsToGraph("Graph4.txt", g);
	DirGraph<string>* rg;
	rg = ReverseGraph(g);
	g.print();
	rg->print();
}

void Task4_5()
{
	DirGraph<string> g;
	FileOfStringsToGraph("Graph2.txt", g);

	g.print();
	cout << endl;
	LQueue<string> q;
	LQueue<string> excluded;
	//excluded.push("b");

	FindAllPathsFromNode("a", "e", 3, 0, g, q, excluded);
}

void Task6()
{
	DirGraph<string> g;
	FileOfStringsToGraph("Graph4.txt", g);
	g.print();
	cout << endl;
	if (isCyclic(g))
		cout << "is cyclic" << endl;
	else
		cout << "is not cyclic" << endl;
}

void Task7()
{
	DirGraph<string> g;
	g.print();
	cout << endl;
	FileOfStringsToGraph("Graph6.txt", g);
	PrintTopological(g);
}

template<typename T>
void PrintPath(pair<int, T>* pred, int indexOfParent)
{
	LStack<T> path;

	while (indexOfParent != -1)
	{
		path.Push(pred[indexOfParent].second);
		indexOfParent = pred[indexOfParent].first;
	}

	cout << path.Pop();

	while (!path.isEmpty())
		cout << " --> " << path.Pop();
	
	cout << endl;
}

template<typename T>
void ShortestPathBetweenTwoNodes(T from, T to, DirGraph<T>& g)
{
	int vCount = g.getVetices().size();
	pair<int, T>* pred = new pair<int, T>[vCount]();
	int parentIndex = -1;
	int lastPred = -1;
	T delimiter; // create an uninitialized variable as a delimiter
	//BFS
	LQueue<T> q;

	q.push(from);
	q.push(delimiter);

	while (!q.isEmpty())
	{
		// Get current element and it's rels
		T current;
		q.pop(current);

		// Skip delimiter
		if (current == delimiter)
		{
			parentIndex++;
			continue;
		}

		// store current in pred[predLast]
		lastPred++;
		pred[lastPred] = make_pair(parentIndex, current);

		// when found "to" print path
		if (current == to)
		{
			PrintPath(pred, lastPred);
			return;
		}

		list<T> currentRels = *g.getVertexRels(current);
		currentRels.pop_front();

		// push nodes current is connected to in the queue
		for (auto& rel : currentRels)
		{
			q.push(rel);
		}
		q.push(delimiter);
	}
}

void Task8()
{
	DirGraph<int> g;
	FileOfIntegersToGraph("Graph.txt", g);
	g.print();
	ShortestPathBetweenTwoNodes<int>(15, 150, g);
}


void swapInArray(int indx1, int indx2, int* arr)
{
	int temp = arr[indx1];
	arr[indx1] = arr[indx2];
	arr[indx2] = temp;
}

// places end element at of array at in a place so elements to the left of it are smaller 
// and elements to the right of it are larger
// then this method is called deeper in the recursion for each left and right partition
int partition(int* arr, int startIndex, int endIndex)
{
	int smaller = startIndex - 1;  // initialize variable to store index of last smaller element
	int pivot = arr[endIndex];     // store the value of the pivot element (end element for every recursion)

	// loop the part given by recursion from start to end-1 (without pivot)
	for (int current = startIndex; current <= endIndex - 1; current++)
	{
		// If current element is smaller than or equal to pivot
		if (arr[current] <= pivot)
		{
			smaller++;    // increment index of last smaller element
			swapInArray(smaller, current, arr);
		}
	}
	swapInArray(smaller + 1, endIndex, arr);
	return (smaller + 1);
}


void QuickSort(int * arr, int startIndex, int endIndex)
{
	if (startIndex < endIndex)
	{
		int index = partition(arr, startIndex, endIndex);
		QuickSort(arr, startIndex, index - 1);
		QuickSort(arr, index + 1, endIndex);
		
	}
}


void SortArray(int* arr, int size)
{
	int steps = 0;
	QuickSort(arr, 0, size - 1);
}

void Task9()
{
	int size = 5;
	int* arr = new int[size]();
	arr[0] = 2;
	arr[1] = 4;
	arr[2] = 5;
	arr[3] = 3;
	arr[4] = 1;


	SortArray(arr, size);
	for (int i = 0; i < size; i++)
		cout << arr[i] << ", ";
	cout << endl;
}

void findMatch(string txt)
{
	// initialize an array that matches the word "start" - finite state automata :D

	int** a = new int*[5];
	for (int i = 0; i < 5; i++)
	{
		a[i] = new int[256];
	}
	// zero fill
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			a[i][j] = 0;
		}
	}
	// set pattern states
	a[0][115] = 1;
	a[1][116] = 2;
	a[2][97] = 3;
	a[3][114] = 4;
	a[4][116] = 5;
	int patternLength = 5;

	// algorithm xD
	int state = 0;
	for (int i = 0; i < txt.length(); i++)
	{
		state = a[state][txt[i]];
		if (state == patternLength)
		{
			state = 0;
			// replace txt from i-(length+1) to i with word here
			txt[i] = 'a';
			txt[i - 1] = 'k';
			txt[i - 2] = 't';
			txt[i - 3] = 'u';
			txt[i - 4] = 'p';
		}
	}
	cout << txt << endl;
}
void Task10()
{
	findMatch("carstartdogstartcar");
}
void task11()
{
	// read/write to file from file
	string output = "";

	ifstream inFile("file.txt");
	string line;
	while (std::getline(inFile, line))
	{
		istringstream iss(line);
		string word;
		while (iss >> word)
		{
			output += word;
			output += "\n";
		}
	}

	ofstream outFile;
	outFile.open("file2.txt");
	outFile << output; // overwrite file with string output
}

int main()
{
	
	cout << endl << endl;
	return 0;
}

