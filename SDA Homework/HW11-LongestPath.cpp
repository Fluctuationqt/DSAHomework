#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Relation 
{
    int from, to;
    long long int weight;
    
    Relation (int from, int to,
              long long int weight) 
    {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
};

class Graph 
{
public:
    vector<Relation*> rels;

    void relate(int u, int v, long long int  w) 
    {
        rels.push_back(new Relation(u, v, w));
    }

    void longestPath(int startVertex, int endVertex, int vCount, int eCount) 
    {
        vector<long long int> dist(vCount + 1, LLONG_MIN);
        dist[startVertex] = 0;

        for (int i = 0; i < vCount; i++) 
        {
            for (int j = 0; j < eCount; j++) 
            {
                Relation* curRel = rels[j];
                
                if (dist[curRel->from] != LLONG_MIN) 
                {
                    int newDist = dist[curRel->from] + curRel->weight;
                    if (dist[curRel->to] < newDist) 
                        dist[curRel->to] = newDist; 
                }
            }
        }

        // Print result
        if (dist[endVertex] == LLONG_MIN)
        {
            cout << "-1" << endl;
            return;
        }
        
        cout << dist[endVertex] << endl;
    }
};

int main () {
    // Initialize
    Graph graph;
    int vCount, eCount, startVertex, endVertex;
    cin >> vCount >> eCount >> startVertex >> endVertex;
    
    // Create Relations
    int from, to;
    long long int weight;
    for (int i = 0; i < eCount; i++) 
    {
        cin >> from >> to >> weight;
        graph.relate(from, to, weight);
    }
    
    // Print Longest Path
    graph.longestPath(startVertex, endVertex, vCount, eCount);
}