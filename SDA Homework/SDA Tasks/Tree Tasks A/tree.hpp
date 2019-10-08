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
public:
	Tree(Node<T>* root = NULL)
		: m_root(root)
	{
	}
	virtual ~Tree();

	void initTestTree();
	void initTestTreeSym();

	Node<T>* getRoot()
	{
		return m_root;
	}

private:
	Node<T>* m_root;

	void del(Node<T> *root);
};

template <typename T>
void Tree<T>::del(Node<T> *root)
{
	if (!root)
		return;
	del(root->left);
	del(root->right);

	delete root;
}

template <typename T>
Tree<T>::~Tree()
{
	del(m_root);
}


template <typename T>
void Tree<T>::initTestTree()
{
	/*
	         9
	      4     3
	   5    5     7
	  1 2  2 1   5 6
	 3        3 8
	*/
	Node<T>
		*n_5_0 = new Node<int>(3, NULL, NULL),
		*n_5_1 = new Node<int>(3, NULL, NULL),
		*n_5_2 = new Node<int>(8, NULL, NULL),

		*n_4_0 = new Node<int>(1, n_5_0, NULL),
		*n_4_1 = new Node<int>(2),
		*n_4_2 = new Node<int>(2),
		*n_4_3 = new Node<int>(1, NULL, n_5_1),
		*n_4_4 = new Node<int>(5, n_5_2, NULL),
		*n_4_5 = new Node<int>(6, NULL, NULL),

		*n_3_0 = new Node<int>(5, n_4_0, n_4_1),
		*n_3_1 = new Node<int>(5, n_4_2, n_4_3),
		*n_3_2 = new Node<int>(7, n_4_4, n_4_5),

		*n_2_0 = new Node<int>(4, n_3_0, n_3_1),
		*n_2_1 = new Node<int>(3, NULL, n_3_2),

		*root = new Node<int>(9, n_2_0, n_2_1);

	m_root = root;
}

template <typename T>
void Tree<T>::initTestTreeSym()
{
	/*
		  3
		1   1
	  2  2 2  2
	*/
	Node<T>
		

		*n_4_0 = new Node<int>(2, NULL, NULL),
		*n_4_1 = new Node<int>(2, NULL, NULL),
		*n_4_2 = new Node<int>(2, NULL, NULL),
		*n_4_3 = new Node<int>(2, NULL, NULL),

		*n_3_0 = new Node<int>(1, n_4_0, n_4_1),
		*n_3_1 = new Node<int>(1, n_4_2, n_4_3),
		
		*root = new Node<int>(9, n_3_0, n_3_1);

	m_root = root;
}