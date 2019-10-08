#pragma once

/*
this method compares if two lists of integers have the same elements ( order doesn't matter)
*/
bool CompareLevel(list<int>* a_level, list<int>* b_level)
{
	a_level->sort();
	b_level->sort();

	int a_size = a_level->size();
	int b_size = b_level->size();

	if (a_size != b_size)
		return false;

	while (a_level->size() > 0)
	{
		if (a_level->front() != b_level->front())
			return false;
		a_level->pop_front();
		b_level->pop_front();
	}
	return true;
}
 
/*
This method compares the two lists of lists generated by GetLevels
if they match (aka each level of a must contain the same elements that the same level in b contains)
*/
bool CompareLevels(list<list<int>*>* a_levels, list<list<int>*>* b_levels)
{
	while (a_levels->size() > 0 && b_levels->size() > 0)
	{
		if (CompareLevel(a_levels->front(), b_levels->front()) == false)
			return false;
		a_levels->pop_front();
		b_levels->pop_front();
	}
	return true;
}

/*
BFS based algorithm to get all the tree levels into a list of lists that looks like this:
levels[0] = list{ 1 }
levels[1] = list{ 2, 3 }
levels[2] = list{ 4, 5, 6, 7}
*/
list<list<int>*>* GetLevels(Node<int>* root)
{
	list<list<int>*>* levels = new list<list<int>*>(); // a list of lists that holds each tree level
	list<int>* currentLevel = new list<int>(); // a temporary variable that holds each level to be pushed into levels
	Node<int>* currentElement; // a temporary variable that holds each tree node to be pushed into currentLevel
	LQueue<Node<int>*> q; // a queue of nodes and delimiters for BFS

						  // Push the root in the queue
	q.push(root);
	q.push(NULL);

	// Pop queue untill empty
	while (q.pop(currentElement))
	{
		// if currentElement is delimiter
		if (currentElement == NULL)
		{
			// push the currentLevel list into the levels list
			levels->push_back(currentLevel);

			// if the queue is empty we are done
			if (q.getSize() == 0)
				break;

			// if it isn't empty push another delimiter and clear the currentLevel
			currentLevel = new list<int>();
			q.push(NULL);
			continue;
		}

		// if currentElement is not a delimiter, then it's a tree node so push it in the
		// current level and add it's children to the queue
		currentLevel->push_back(currentElement->data);
		if (currentElement->left != NULL)
			q.push(currentElement->left);
		if (currentElement->right != NULL)
			q.push(currentElement->right);
	}

	return levels;
}