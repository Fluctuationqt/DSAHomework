#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    int data;
    int parent;
    
    Node() {
        data = 0;
        parent = 0;
    }
    
    Node(int d) {
        data = d;
        parent = 0;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;

    vector<Node> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes.at(i) = Node(i + 1);
    }

    for (int i = 1; i <= n - 1; i++) {
        int node, rel;
        cin >> node >> rel;
        Node* nodeFrom = &nodes.at(node - 1);
        Node* nodeTo = &nodes.at(rel - 1);

        if (nodes.at(rel - 1).parent != 0) {
            nodeFrom->parent = nodeTo->data;
        }
        else {
            nodeTo->parent = nodeFrom->data;
        }
    }
    
    int q;
    cin >> q;
    for (int i = 0; i<q; i++) {
        int node, k;
        cin >> node >> k;

        int idx = node - 1;
        for (int i = 0; i < k; i++) {
            idx = nodes.at(idx).parent - 1;
        }
        cout << nodes.at(idx).data << endl;
    }
    return 0;
}