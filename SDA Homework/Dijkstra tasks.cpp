#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <limits>

using namespace std;
typedef unsigned long ulong;
const ulong INF = numeric_limits<ulong>::max();

struct edge;

struct vertex {
    int key;
    ulong d;
    vector<edge*> edges;
    
    vertex (int k) {
        key = k;
    d = INF;
    }
};

struct edge {
    vertex *v;
    ulong w;
    edge (vertex* vertx, ulong weight) {
    v = vertx;
    w = weight;
    }
};

class graph {
public:
    map<int, vertex*> vertices;
    
    void add_vertex(int v) {
        vertex *vv = new vertex(v);
    vertices.insert(pair<int,vertex*>(v, vv));
    }
    
    void add_edge(int u, int v, ulong w) {
        vertex *uu = find(u);
        vertex *vv = find(v);
        
        vv->edges.push_back(new edge(uu, w));
        uu->edges.push_back(new edge(vv, w));
    }
    
    vertex* find (int k) {
        vertex* v = nullptr;
        
        auto it = vertices.find(k);
        if (it != vertices.end()) {
            v = it->second;
        }
        
        return v;
    }
    
    void bfs(int vertex) {
        auto start = vertices.find(vertex);
        bfs_vertex(start->second);

        for (auto &pair : vertices) {
        if (pair.first != vertex) {
        if (pair.second->d == INF) {
            cout << "-1 ";
        }
        else {
            cout << pair.second->d << " ";
        }
        }
    }
    
    cout << endl;
    }
    
    void bfs_vertex (vertex *s) {
    priority_queue<pair<ulong, vertex*>,
               vector<pair<ulong,vertex*> >,
               greater<pair<ulong,vertex*> > > q;
    s->d = 0;
    q.push({0, s});

    while (q.empty() == false) {
        ulong d = q.top().first;
        vertex *u = q.top().second;
        q.pop();
        
        if (u->d != d) 
        continue;
        
        for (int i = 0; i < u->edges.size(); i++) {
        edge *e = u->edges[i];
        
        if (e->v->d > u->d + e->w) {
            e->v->d = u->d + e->w;     
            q.push({e->v->d, e->v});
        }
        }
    }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;

    while (tests > 0) {
    graph g;
    int vertices, edges;
    cin >> vertices >> edges;
    for (int i = 1; i <= vertices; i++) {
        g.add_vertex(i);
    }
    
    int u,v,w;
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> w;
        g.add_edge(u,v,w);
    }

    int vertex;
    cin >> vertex;
    g.bfs(vertex);
    tests--;
    }
}


// 2
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef long long llong;
const llong NINF = numeric_limits<llong>::min();

struct edge {
    int u;
    int v;
    llong w;
    edge (int u, int v, llong w) {
    this->u = u;
    this->v = v;
    this->w = w;
    }
};

class graph {
public:
    int vertecies;
    vector<edge*> edges;

    graph(int n, int m) {
    vertecies = n;
    //edges = vector<edge*>(m + 1);
    }

    void add_edge(int u, int v, llong w) {
    edge *e = new edge(u, v, w);
    edges.push_back(e);
    }

    void bellman_ford(int s, int t) {
    vector<llong> d(vertecies + 1, NINF);
    d[s] = 0;

    for (int i = 0; i < vertecies; i++) {
        for (int j = 0; j < edges.size(); j++) {
        if (d[edges[j]->u] != NINF) {
            if (d[edges[j]->u] + edges[j]->w > d[edges[j]->v]) {
            d[edges[j]->v] = d[edges[j]->u] + edges[j]->w; 
            }
        }
        }
    }

    if (d[t] == NINF) {
        cout << "-1\n";
    }
    else {
        cout << d[t] << endl;
    }
    }
};

int main () {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    graph g(n, m);
    int u,v;
    llong w;
    for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    g.add_edge(u, v, w);
    }
    
    g.bellman_ford(s, t);
}

// 3

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdint>

using namespace std;
enum color { white, black };
struct edge;

struct vertex {
    int key;
    color c;
    uint64_t d;
    edge *p;
    vector<edge*> edges;
    map<int, edge*> railways;
    
    vertex(int k) {
    key = k;
    c = white;
    p = nullptr;
    d = ULLONG_MAX;
    }
};

struct edge {
    uint64_t w;
    vertex* v;
    bool rail;
    bool from_sp;
    
    edge (uint64_t weight, vertex* to, bool is_rail = false) {
    w = weight;
    v = to;
    rail = is_rail;
    from_sp = false;
    }
};

struct graph {
    map<int, vertex*> vertices;
    int c = 0;

    void add_edge(int u, int v, uint64_t w) {
    vertex* uu = this->find(u);
    vertex* vv = this->find(v);

    if (uu == nullptr) {
        uu = new vertex(u);
        vertices.insert({u, uu});
    }
    
    if (vv == nullptr) {
        vv = new vertex(v);
        vertices.insert({v, vv});
    }

    uu->edges.push_back(new edge(w, vv));
    vv->edges.push_back(new edge(w, uu));
    }

    void add_railway(int u, uint64_t w) {
    vertex *s = this->find(1);
    vertex *uu = this->find(u);
    auto it = s->railways.find(u);
    if (it == s->railways.end()) {
        s->railways.insert({u, new edge(w, uu, true)});
    }
    else {
        if (it->second->w > w) {
        it->second->w = w;
        }
        c++;
    }
    }
    
    void find_useless_railways() {
    vertex* s = this->find(1);
    merge_railways_to_edges(s);
    this->dijkstra(s);
    
    for (int i = 0; i < s->edges.size(); i++) {
        if (s->edges[i]->rail && s->edges[i]->from_sp == false) {
        c++;
        }
    }

    cout << c << endl;
    }

    void merge_railways_to_edges(vertex *s) {
    for (auto it : s->railways) {
        s->edges.push_back(it.second);
    }
    }

    void print () {
    for (auto it : vertices) {
        if (it.first == 0) {
        continue;
        }
        
        cout << "Vertex: " << it.second->key
         << ", Distanse: " << it.second->d << endl;
        for (int i = 0; i < it.second->edges.size(); i++) {
        edge* e = it.second->edges[i];
        cout << "\t" << e->v->key << " " << e->w << endl;
        }
        cout << endl;
    }
    }

private:
    void dijkstra (vertex* s) {
    priority_queue<pair<uint64_t, vertex*>,
               vector<pair<uint64_t, vertex*>>,
               greater<pair<uint64_t, vertex*>>> q;

    s->d = 0;
    q.push({0, s});
    while (q.empty() == false) {
        uint64_t dis = q.top().first;
        vertex *u = q.top().second;
        q.pop();

        if (dis != u->d) continue;
        
        for (int i = 0; i < u->edges.size(); i++) {
        edge* e = u->edges[i];
        vertex *v = e->v;

        if (v->d > u->d + e->w) {
            v->d = u->d + e->w;
            q.push({v->d, v});
            if (v->p != nullptr) {
            v->p->from_sp = false;
            }
            v->p = e;
        }
        else if (v->d == u->d + e->w) {
            if (v->p->rail == false) {
            continue;
            }
            if (e->rail == false) {
            if (v->p != nullptr) {
                v->p->from_sp = false;
            }
            v->p = e;
            }
        }
        }

        if (u->p != nullptr) {
        u->p->from_sp = true;
        }
    }
    }
    
    vertex* find(int u) {
    vertex* v = nullptr;
    auto it = vertices.find(u);
    if (it != vertices.end()) {
        v = it->second;
    }
    return v;
    }

    
};

int main () {
    ios_base::sync_with_stdio(false);
    
    int vertices, edges, railways;
    cin >> vertices >> edges >> railways;
    graph g;
    int u, v;
    uint64_t w;
    for (int i = 0; i < edges; i++) {
    cin >> u >> v >> w;
    g.add_edge(u, v, w);
    }

    for (int i = 0; i < railways; i++) {
    cin >> u >> w;
    g.add_railway(u, w);
    }
    g.find_useless_railways();
    //g.print();
}