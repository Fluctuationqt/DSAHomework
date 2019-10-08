/* ######### GRAPH ############ */
template <typename T>
class DirGraph {
public:
	void addVertex(const T& v); // без проверка дали вече го има този връх
	void removeVertex(const T& v); // маха връх и всички връзки към него
	bool hasVertex(const T& v) const;
	void addEdge(const T& vFrom, const T& vTo); // без проверки съществуват ли върховете
	void removeEdge(const T& vFrom, const T& vTo); // премахва ребро
	bool hasEdge(const T& vFrom, const T& vTo) const; // има ребро => true
	list<T>* getVertexRels(const T& v); // Връща върха + релациите му
	list<T> getVetices() const; // Връща върховете
	void print() const;
protected:
	list<list<T> > linkedGraph;
};


/* #######  TREE  ############ */
template <class T>
struct Node {
	T data;
	Node *left,
		*right;

	Node(T _data = T(), Node* _left = NULL, Node* _right = NULL)
		: data(_data)
		, left(_left)
		, right(_right)
	{
	}
};
template <typename T>
class Tree {
private:
	Node<T>* m_root;
	void del(Node<T> *root);
public:
	Tree(Node<T>* root = NULL)
		: m_root(root)
	{
	}
	virtual ~Tree();
	Node<T>* getRoot();
	
friend ostream& operator<<(ostream& out, const Tree<T> &t)
	{
		printInorder(t.m_root, out);
		out << endl;
		return out;
	}
static void printInorder(Node<T>* root, ostream& out)
	{
		if (root == NULL)
			return;
		printInorder(root->left, out);
		out << root->data << " ";
		printInorder(root->right, out);
	}
	void initTestTree()
	{
		Node<T>
		*n_2_0 = new Node<int>(4, NULL, NULL),
		*n_2_1 = new Node<int>(12, n_3_2, n_3_3),
		*root = new Node<int>(8, n_2_0, n_2_1);
		m_root = root;
	}
};

/* СПИСЪЦИ ИТЕРИРАНЕ И ТРИЕНЕ и REVERSE()-ване */
for(auto& it = list.begin(); it != list.end(); it++)
{	
	if (*it == forRemoval)
	{
		it = list.erase(nodeIT);// list becomes smaller
		it--;// move back to actual element
	}
}

static void reverse(struct Node** head_ref) // in C
{
    struct Node* prev   = NULL;
    struct Node* current = *head_ref;
    struct Node* next;
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    *head_ref = prev;
}