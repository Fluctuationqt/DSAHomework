// GRaphhhh.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include <string>
#include <queue>
#include <stack>
using namespace std;

DirGraph<string>* ReadGraphFromFile(string fileName)
{
	DirGraph<string>* g = new DirGraph<string>();
	ifstream inFile(fileName);
	string line;
	
	// loop through all the lines
	while (getline(inFile, line))
	{
		istringstream iss(line);
		string word;
		int counter = 0;
		string firstWord = "";
		
		// loop through all the words in line
		while (iss >> word)
		{
			if (counter == 0)
			{
				// create a vertex with the first word
				firstWord = word;
				if(!g->hasVertex(word))
					g->addVertex(word);
			}
			else
			{
				// create an edge to any other word
				g->addEdge(firstWord, word);
				// if the word doesn't exist as a vertex
				// create a new vertex with it
				if (!g->hasVertex(word))
					g->addVertex(word);
			}
			counter++;
		}
	}
	return g;
}

// BFS
void BFS(DirGraph<string>& g, string start)
{
	list<string> visited;
	queue<string> q;
	q.push(start);
	visited.push_back(start);
	
	while (!q.empty())
	{
		string current = q.front(); q.pop();
		cout << current;
		list<string>* current_vrels = g.getVertexRels(current); // get start vertex's relations
		auto& it = current_vrels->begin(); it++; // skip first node, which is current vertex
		while (it != current_vrels->end())
		{
			if (find(visited.begin(), visited.end(), *it) == visited.end())
			{
				q.push(*it);
				visited.push_back(*it);
			}
			it++;
		}
	}
	
}


// DFS WITH STACK
void DFS(DirGraph<string>& g, string start)
{
	list<string> visited;
	stack<string> q;
	q.push(start);
	visited.push_back(start);

	while (!q.empty())
	{
		string current = q.top(); q.pop();
		cout << current;
		list<string>* current_vrels = g.getVertexRels(current); // get start vertex's relations
		auto& it = current_vrels->begin();
		it++; // skip first node, which is current vertex
		for(it; it != current_vrels->end(); it++)
		{
			if (find(visited.begin(), visited.end(), *it) == visited.end())
			{
				q.push(*it);
				visited.push_back(*it);
			}
		}
	}
}

// DFS Recursive
void DFSR(DirGraph<string> & g, string start, list<string> visited)
{
	cout << start;
	visited.push_back(start);
	list<string>* vrels = g.getVertexRels(start);
	auto& it = vrels->begin();
	it++;
	for (it; it != vrels->end(); it++)
	{
		if (find(visited.begin(), visited.end(), *it) == visited.end())
		{
			DFSR(g, *it, visited);
		}
	}
	//visited.remove(start);
}

// Print all paths from vertex to vertex
void PrintAllPaths(DirGraph<string>& g, string from, string to, list<string> visited, list<string> path)
{
	visited.push_back(from);
	path.push_back(from);

	if (from == to)
	{
		for (auto& node : path)
		{
			cout << node << "->";
		}
		cout << endl;
	}
	else
	{
		list<string>* currentRels = g.getVertexRels(from);
		auto& it = currentRels->begin();
		it++;

		while (it != currentRels->end())
		{
			if (find(visited.begin(), visited.end(), *it) == visited.end())
			{
				PrintAllPaths(g, *it, to, visited, path);
			}
			it++;
		}
	}
	
	visited.remove(from);
}
 
// Utility function for topological sorting of the graph.
void TopologicalUtil(DirGraph<string>& g, string v, list<string> visited,
 list<string>& allVisited, stack<string>& sort)
{
	visited.push_back(v);
	allVisited.push_back(v);

	list<string>* rels = g.getVertexRels(v);
	auto& it = rels->begin();
	it++;
	for (it; it != rels->end(); it++)
	{
		if (find(visited.begin(), visited.end(), *it) == visited.end() 
			&& find(allVisited.begin(), allVisited.end(), *it) == allVisited.end())
		{
			TopologicalUtil(g, *it, visited, allVisited, sort);
		}
	}
	sort.push(v);
}

// Graph topological sorting
void Topological(DirGraph<string>& g)
{
	stack<string> sort;
	list<string> visited, allVisited;
	list<string> vertices = g.getVetices();
	for (auto& v : vertices)
	{
		if (find(allVisited.begin(), allVisited.end(), v) == allVisited.end())
		{
			TopologicalUtil(g, v, visited, allVisited, sort);
		}
	}

	while(!sort.empty())
	{
		cout << sort.top() << " ";
		sort.pop();
	}
	cout << endl;
}

void PrintAllWords(DirGraph<string>& g, string vFrom)
{
	list<string> vertices = g.getVetices();
	list<string> temp1, temp2;
	for (auto& vTo : vertices)
	{
		if (vFrom != vTo)
		{
			PrintAllPaths(g, vFrom, vTo, temp1, temp2);
		}
	}
}

int main()
{
	DirGraph<string>* graph = ReadGraphFromFile("Graph2.txt");
	graph->removeVertex("2");
	graph->print();
	list<string> visited;
	list<string> path;
	
	//PrintAllPaths(*graph, "a", "c", visited, path);
	
	/*
	PrintAllWords(*graph, "2");
	cout << endl;
	BFS(*graph, "2");
	cout << endl;
	DFS(*graph, "2");
	cout << endl;
	DFSR(*graph, "2", visited);
	cout << endl;*/
	Topological(*graph);
	
	cout << endl;
    return 0;
}

