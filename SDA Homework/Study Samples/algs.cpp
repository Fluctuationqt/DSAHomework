
/*
	############## GRAPH ################
*/

// 1. BFS, DFS

// RECURSIVE DFS
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

// BFS - replace 'queue' with 'stack' and 'front' with 'top' for iterative DFS
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

// 2. Всички пътища от връх до връх
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

// 3. Топологична сортировка
/*
	Топологична сортировка
	1. list<T> visited, allvisited
	2. stack<T> result
	3. от стартиращата функция пусни DFS за всички елементи които не са във allVisited
	4. стартирай DFS като подавай allvisited и sort като референция(&) а visited като копие
	5. в началото на DFS добавяй сегашния елемент към visited и allVisited
	6. преди да пуснеш рекурсия навътре за всеки връх от релациите проверявай дали върха го 
	   няма във visited или allVisited
	7. накрая на DFS-то добави в result върха
	8. в стартиращата функция изпопвай и принтирай стека
	Резултат: отляво са независимите отдясно са зависимите 4 5 2 3 1 0
*/




/* 
	######## ДЪРВЕТА ###################
*/

// 1. EXPRESSION TREE
Node<char>* exprTree(string expr)
{
	stack<Node<char>*> st;
	for (int i = expr.length() - 1; i >= 0; i--)
	{
		char current = expr[i];
		if (current >= '0' && current <= '9')
		{
			// operand -> push
			st.push(new Node<char>({ current, NULL, NULL }));
		}
		else if (current == '+' || current == '*' || current == '/' || current == '-')
		{
			// operator -> pop two operands and make them children of the operator
			Node<char>* left = st.top(); st.pop();
			Node<char>* right = st.top(); st.pop();
			st.push(new Node<char>({ current, left, right }));
		}
	}

	if (st.size() == 1) {
		Node<char>* result = st.top();
		st.pop();
		return result;
	}
	else
	{
		throw exception("invalid expression");
	}

}
void PrintPostorder(Node<char>* root)
{
	if (root == NULL)
		return;
	PrintPostorder(root->left);
	PrintPostorder(root->right);
	cout << root -> data;
}
void PrintPreorder(Node<char>* root)
{
	if (root == NULL)
		return;
	cout << root->data;
	PrintPreorder(root->left);
	PrintPreorder(root->right);
}
void PrintInorder(Node<char>* root)
{
	if (root == NULL)
		return;
	PrintInorder(root->left);
	cout << root->data;
	PrintInorder(root->right);
}

int EvalTree(Node<char>* root)
{
	// if null return 0
	if (root == NULL)
		return 0;

	// if operand parse it and return it
	if (root->data >= '0' && root->data <= '9')
		return root->data - '0';

	// if operator get it's left and right operands and return it's calculation
	int a = EvalTree(root->left);
	int b = EvalTree(root->right);
	return calculate(a, b, root->data);
}


// 2. FIND TRACE, FIND PATH, ISSYMETRICAL
bool FindTrace(Node<int>* root, int element, string& trace)
{
	if (root == NULL)
		return false;

	if (root->data == element)
		return true;

	bool foundL = FindTrace(root->left, element, trace);
	bool foundR = FindTrace(root->right, element, trace);

	if (foundL)	trace += "l";
	if (foundR)	trace += "r";
	
	return (foundL || foundR);
}

bool FindPath(Node<int>* root, int element, string& path)
{
	if (root == NULL)
		return false;

	if (root->data == element)
	{
		path += to_string(root->data) + " ";
		return true;
	}
	
	bool foundL = FindPath(root->left, element, path);
	bool foundR = FindPath(root->right, element, path);
	if (foundL || foundR)
	{
		path += to_string(root->data) + " ";
	}
	return (foundL || foundR);
}

bool isSymetrical(Node<int>* root1, Node<int>* root2)
{
	if (root1 == NULL && root2 == NULL)
		return true;
	if (root1->data == root2->data)
		return isSymetrical(root1->left, root2->right) 
			&& isSymetrical(root1->right, root2->left);
	return false;
}

// 3. GET DEPTH
int GetDepth(Node<int>* root)
{
	if (root == NULL)
		return 0;
	int leftDepth = GetDepth(root->left);
	int rightDepth = GetDepth(root->right);
	if (leftDepth > rightDepth)
		return leftDepth + 1;
	else
		return rightDepth + 1;
}

// 5. PRINT LEVEL, PRINT LEVEL
void printGivenLevel(Node<int>* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        cout << root->data;
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

// with BFS
void PrintLevels(Node<int>* root)
{
	Node<int>* delim = new Node<int>();
	queue<Node<int>*> q;
	q.push(root);
	q.push(delim);
	int currentLevel = 0;
	cout << "Level0: ";
	while (!q.empty())
	{
		Node<int>* current = q.front();
		q.pop();
		if (current == delim && !q.empty())
		{
			q.push(delim);
			currentLevel++;
			cout << endl << "Level" << currentLevel << ": ";
			continue;
		}

		if (delim != current)
		{
			cout << current->data << " ";
		}
		
		if (current->left != NULL)
			q.push(current->left);
		if (current->right != NULL)
			q.push(current->right);
				
	}
	cout << endl;
}

/*
	ОПЕРАЦИИ С ФАЙЛОВЕ - 
		Даден е файл с редове: 
		2
		Mike D: 2S 3C 4S 
		Peter F: 5C AS
		
		първото число от ред 1 е броя играчи
		имената на играчите са: Mike D и Peter F 
		другото са им картите S - спатия C-купа... etc..
*/

enum color{S,C,H,D};
/*
Може да се ползва и структура за всяка карта
struct card
{
	color c;
	char t;
};*/

class Player
{
public:
	string name;
	list<string> cards;
};

color GetColor(string card)
{
	if (card[1] == 'S')
		return color::S;
	if (card[1] == 'C')
		return color::C;
}

void ReadFile(string fileName, list<Player>& players)
{
	ifstream inFile(fileName);
	string line;
	int lineCounter = 0;
	while (getline(inFile, line))
	{
		if (lineCounter == 0)
		{
			lineCounter++;
			continue;
		}
		
		bool haveName = false;
		istringstream iss(line);
		string word, name="", cards="";
		Player* p = new Player();
		p->name = "";
		while (iss >> word)
		{
			if (word[word.length() - 1] == ':')
			{
				haveName = true;
				p->name += " " + word.substr(0, word.length() - 1);
				continue;
			}
			if(!haveName)
				p->name += word;
			if (haveName)
			{
				p->cards.push_back(word);
			}
		}
		players.push_back(*p);
		lineCounter++;
	}
}

/* СОРТИРОВКИ HEAPSORT, MERGESORT, QUICKSORT */

// 1. HEAPSORT
// left child index  of parent at index i in a heap
int LeftChildIndex(int i)
{
	return 2 * i + 1;
}

// right child index of parent at index i in a heap
int RightChildIndex(int i)
{
	return 2 * i + 2;
}

// sawp two elements in a vector by their indices
void swap(int indx1, int indx2, vector<int>& v)
{
	int temp = v[indx1];
	v[indx1] = v[indx2];
	v[indx2] = temp;
}

// turn a vector<int> into a heap upto the element at index=size()
void max_heapify(vector<int> & v, int size, int parent_index)
{
	int largest_index = parent_index;
	int left_index = LeftChildIndex(parent_index);
	int right_index = RightChildIndex(parent_index);
	
	// check if left is largest
	if (left_index < size && v[left_index] > v[largest_index])
	{
		largest_index = left_index;
	}

	// check if right is largest
	if (right_index < size && v[right_index] > v[largest_index])
	{
		largest_index = right_index;
	}

	// if root isn't largest swap it with largest and heapify again
	if (parent_index != largest_index)
	{
		swap(parent_index, largest_index, v);
		max_heapify(v, size, largest_index);
	}
}

// make an entire vector a heap
void build_max_heap(vector<int> & v)
{
	int size = v.size();
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		max_heapify(v, size, i);
	}
}

// sort a vector
void heap_sort(vector<int> & v)
{
	int size = v.size();
	// One by one extract an element from heap
	for (int i = size - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(0, i, v);

		// call max heapify on the reduced heap
		max_heapify(v, i, 0);
	}
}

// 2. MERGESORT
/*
	MergeSort(arr[], l,  r)
	If r > l
	1. Find the middle point to divide the array into two halves:
		middle m = (l+r)/2
	2. Call mergeSort for first half:
		Call mergeSort(arr, l, m)
	3. Call mergeSort for second half:
		Call mergeSort(arr, m+1, r)
	4. Merge the two halves sorted in step 2 and 3:
		Call merge(arr, l, m, r)
*/
void Merge(vector<int>& arr, int l, int mid, int r)
{
	// create temp arrays
	int leftSize = mid - l + 1;
	int rightSize = r - mid;
	vector<int> left(leftSize);
	vector<int> right(rightSize);
	
	// copy data into temp arrays
	for (int i = 0; i < leftSize; i++)
		left[i] = arr[l + i];
	for (int j = 0; j < rightSize; j++)
		right[j] = arr[mid + 1 + j];

	// copy the bigger from left[i] or right[j] back into arr[k]
	// this loop stops if either left or right has been copied fully
	int i = 0, j = 0, k = l;
	while (i < leftSize && j < rightSize)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	// copy any elements of left[i] if there are any more left
	while (i < leftSize)
	{
		arr[k] = left[i];
		i++;
		k++;
	}

	// copy any elements of right[j] if there are any more left
	while (j < rightSize)
	{
		arr[k] = right[j];
		j++;
		k++;
	}
}
void MergeSort(vector<int>& arr, int l, int r)
{
	if (r > l)
	{
		int mid = (l + r) / 2;
		MergeSort(arr, l, mid);
		MergeSort(arr, mid + 1, r);
		Merge(arr, l, mid, r);
	}
}

// 3. BINARY SEARCH
int BinarySearch(vector<int>& arr, int from, int to, int value)
{
	if (from <= to)
	{
		int mid = from + ((to - from) / 2);

		if (value < arr[mid])
		{
			return BinarySearch(arr, from, mid-1, value);
		}
		else if (value > arr[mid])
		{
			return BinarySearch(arr, mid+1, to, value);
		}
		else if (value == arr[mid])
		{
			return mid;
		}
	}
	return -1;
}

// 4. QUICKSORT
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