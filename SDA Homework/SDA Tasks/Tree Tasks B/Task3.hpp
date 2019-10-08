#pragma once

void Path(Vertex<string>* from, Vertex<string>* target, float weight, list<Vertex<string>*>& visited, list<Vertex<string>*> path, list<string> enemies)
{
	path.push_back(from);

	if (find(enemies.begin(), enemies.end(), from->getData()) != enemies.end())
	{

		throw exception("Letter destroyed");
	}

	if (from == target)
	{
		cout << "Mail receive chance: ";
		cout << weight << endl;
		for (auto& p : path)
		{
			cout << p->getData() << "->";
		}
		cout << endl;

	}

	visited.push_back(from);

	for (auto& rel : from->getRelations())
	{
		if (find(visited.begin(), visited.end(), rel->to()) == visited.end())
		{
			Path(rel->to(), target, rel->getWeight()*weight, visited, path, enemies);
		}
	}
}

list<string> ReadEnemiesFromFile(string filename, string me)
{
	list<string> enemies;
	ifstream file(filename);
	string line;
	while (getline(file, line))
	{
		string hater, hated;
		istringstream iss(line);
		if (!(iss >> hater >> hated)) { throw exception("Wrong file, dumbass"); }
		if (me == hated)
		{
			enemies.push_back(hater);
		}
	}
	return enemies;
}

void SendMail(Graph<string> * friends, string from, string to)
{
	list<Vertex<string>*> temp;
	list<Vertex<string>*> visited;
	list<string> enemies = ReadEnemiesFromFile("enemies.txt", from);
	auto fromVertex = friends->findVertex(from);
	auto toVertex = friends->findVertex(to);
	try {
		Path(fromVertex, toVertex, 1.0, visited, temp, enemies);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
}