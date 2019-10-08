#pragma once
#include <sstream>
#include <fstream>
#include <istream>
#include <string>

using namespace std;
template<typename T>
class Vertex;

template<typename T>
class Relation
{
private:
	float _weight;
	Vertex<T>* _to;
public:
	Relation(float weight, Vertex<T>* to)
	{
		_weight = weight;
		_to = to;
	}

	float getWeight()
	{
		return _weight;
	}

	Vertex<T>* to()
	{
		return _to;
	}
};

template<typename T>
class Vertex
{
private:
	T _data;
	list<Relation<T>*> _relations;

public:
	Vertex(T data)
	{
		_data = data;
	}
	
	~Vertex()
	{
		while(_relations.size() > 0)
		{
			Relation<T>* rel = _relations.front();
			_relations.pop_front();
			delete rel;
		}
	}

	void AddRelation(float weight, Vertex<T>* to)
	{
		Relation<T>* relation = new Relation<T>(weight, to);
		_relations.push_back(relation);
	}

	bool hasRelation(Vertex<T>* to)
	{
		for (auto& rel : _relations)
		{
			if (rel->to() == to)
				return true;
		}
		return false;
	}

	Relation<T>* GetRelation(Vertex<T>* to)
	{
		for (auto& rel : _relations)
		{
			if (rel->to() == to)
				return rel;
		}
		return nullptr;
	}
	
	list<Relation<T>*> getRelations()
	{
		return _relations;
	}

	T getData()
	{
		return _data;
	}
	
	void Print()
	{
		cout << _data << " : ";
		for (auto& rel : _relations)
		{
			cout << "(" << rel->to()->getData() << ", " << rel->getWeight() << ")  ";
		}
		cout << endl;
	}
};

template<typename T>
class Graph
{
private:
	list<Vertex<T>*> _vertices;

public:
	~Graph()
	{
		while (_vertices.size() > 0)
		{
			Vertex<T>* vertex = _vertices.front();
			_vertices.pop_front();
			delete vertex;
		}
	}

	Vertex<T>* addVertex(T data)
	{
		Vertex<T>* vertex = new Vertex<T>(data);
		_vertices.push_back(vertex);
		return vertex;
	}
	
	Vertex<T>* findVertex(T data)
	{
		for (auto& vertex : _vertices)
		{
			if (vertex->getData() == data)
			{
				return vertex;
			}
		}
		return nullptr;
	}

	void AddRelation(Vertex<T>* from, Vertex<T>* to, float weight)
	{
		from->AddRelation(weight, to);
	}

	void FromFile(string filename)
	{
		ifstream file(filename);
		string line;
		while (getline(file, line))
		{
			istringstream iss(line);
			string from, to, weight;
			string trash;
			if (!(iss >> from >> trash >> to >> trash >> weight)) { throw exception("invalid file"); }
			
			// look for a vertex
			Vertex<T>* vertexFrom = findVertex(from);
			Vertex<T>* vertexTo = findVertex(to);
			
			// if a vertex doesn't exist add it and get it's pointer
			if(vertexFrom == nullptr)
			{ 
				vertexFrom = addVertex(from);
			}

			if (vertexTo == nullptr)
			{
				vertexTo = addVertex(to);
			}

			// relate both vertices with the same weight
			vertexFrom->AddRelation(stof(weight), vertexTo);
			vertexTo->AddRelation(stof(weight), vertexFrom);

		}

	}

	void Print()
	{
		for (auto& vertex : _vertices)
		{
			vertex->Print();
		}
	}
};