#pragma once
#include <algorithm>
#include <iostream>
#include <list>

#include <sstream>

using std::list;
using std::cout;
using std::endl;

/**
* Restrictions:
* - unique vertices
*/
template <typename T>
class DirGraph {
public:
	void addVertex(const T& v);
	void removeVertex(const T& v);
	bool hasVertex(const T& v) const;


	void addEdge(const T& vFrom, const T& vTo);
	void removeEdge(const T& vFrom, const T& vTo);
	bool hasEdge(const T& vFrom, const T& vTo) const;

	list<T>* getVertexRels(const T& v);
	list<T> getVetices() const;

	void print() const;

protected:
	list<list<T> > linkedGraph;
};


template <typename T>
list<T>* DirGraph<T>::getVertexRels(const T& v)
{
	auto verticesIt = linkedGraph.begin(),
		end = linkedGraph.end();

	while (verticesIt != end) {
		if (verticesIt->front() == v)
			return &(*verticesIt);
		verticesIt++;
	}
	return NULL;
}

template <typename T>
void DirGraph<T>::addVertex(const T& v)
{
	list<T> vertex;
	vertex.push_front(v);

	linkedGraph.push_back(vertex);
}

template <typename T>
void DirGraph<T>::print() const
{
	cout << "Vertex -- Refs" << endl;
	cout << "-----------------" << endl;
	for (auto& vertexRefs : linkedGraph) {
		for (auto& ref : vertexRefs)
			cout << ref << ' ';
		cout << endl;
	}
}

template <typename T>
void DirGraph<T>::removeVertex(const T& v)
{
	auto verticesIt = linkedGraph.begin();
	auto end = linkedGraph.end();
	
	// loop node lists to end of graph
	while (verticesIt != end) 
	{
		// current list's front element is v, delete the list
		if (verticesIt->front() == v)
		{
			verticesIt = linkedGraph.erase(verticesIt); // iterator moves to next element but list becomes smaller
			verticesIt--; // move back once to be on next actual element
		}
		else // if it's front element is not v, enter the list and search for v in the elements and delete if found
		{
			auto nodeIT = verticesIt->begin();
			auto nodeEndIT = verticesIt->end();
			
			while (nodeIT != nodeEndIT)
			{
				T nodeItData = (*nodeIT); // get object behind iterator which is an integer
				if (nodeItData == v)
				{
					verticesIt->erase(nodeIT);
					break;
				}
				
				nodeIT++;
			}
		}
		verticesIt++;
	}
}

template <typename T>
void DirGraph<T>::addEdge(const T& vFrom, const T& vTo)
{
	for (auto& vertexRels : linkedGraph) {
		if (vertexRels.front() == vFrom) {
			vertexRels.push_back(vTo);
			break;
		}
	}
}

template <typename T>
void DirGraph<T>::removeEdge(const T& vFrom, const T& vTo)
{
	list<T>* vertexRels = getVertexRels(vFrom);

	if (!vertexRels->empty()) {
		auto elemIterator = std::find(vertexRels->begin(), vertexRels->end(), vTo);
		// there exists such relation
		if (*elemIterator == vTo) {
			vertexRels->erase(elemIterator);
		}
	}
}

template <typename T>
bool DirGraph<T>::hasVertex(const T& v) const
{
	auto verticesIt = linkedGraph.begin(),
		end = linkedGraph.end();

	for (; verticesIt != end && verticesIt->front() != v; verticesIt++) {
	}

	return verticesIt != end;
}



template <typename T>
bool DirGraph<T>::hasEdge(const T& vFrom, const T& vTo) const
{
	auto verticesIt = linkedGraph.begin();
	auto end = linkedGraph.end();

	// loop node lists to end of graph
	while (verticesIt != end)
	{
		// current list's front element is v, delete the list
		if (verticesIt->front() == vFrom)
		{
			auto nodeIT = verticesIt->begin();
			auto nodeEndIT = verticesIt->end();

			while (nodeIT != nodeEndIT)
			{
				auto nodeItData = (*nodeIT); // get object behind iterator which is an integer
				if (nodeItData == vTo)
				{
					return true;
				}

				nodeIT++;
			}
		}
		verticesIt++;
	}

	return false;
}

template <typename T>
list<T> DirGraph<T>::getVetices() const
{
	list<T> vertices;
	for (auto& vertexRels : linkedGraph)
		vertices.push_back(vertexRels.front());

	return vertices;
}