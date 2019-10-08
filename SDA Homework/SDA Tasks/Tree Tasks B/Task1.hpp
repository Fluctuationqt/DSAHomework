#pragma once

void PrintElementAndDescendants(int n, int desc, int x, int y)
{
	if (desc == -1)
		std::cout << n << " has " << 0 << " children in range (" << x << ", " << y << "); ";
	else
		std::cout << n << " has " << desc << " children in range (" << x << ", " << y << "); ";
	if (desc % 2 == 0 && desc != 0)
		std::cout << "so we sum it.";
	std::cout << std::endl;
}

bool inRange(int n, int x, int y)
{
	return (n >= x && n <= y);
}

/* returns the count of the elements in range [x, y] from the tree
	example tree:
	3
	1 2

	=> 3 if x = 1, y = 3
	=> 2 if x = 1, y = 2
	=> 1 if x = 1, y =1
*/
int countDescendantsInRange(Node<int>* node, int x, int y)
{
	if (node == NULL)
		return 0;

	int leftSum = countDescendantsInRange(node->left, x, y);
	int rightSum = countDescendantsInRange(node->right, x, y);

	if (inRange(node->data, x, y))
		return leftSum + rightSum + 1;
	else
		return leftSum + rightSum;
}

// task1 solution
int SumElementsWithEvenCountOfDescendantsInRange(Node<int>* node, int x, int y)
{
	if (node == NULL)
		return 0;

	// get left right sum
	int leftSum = SumElementsWithEvenCountOfDescendantsInRange(node->left, x, y);
	int rightSum = SumElementsWithEvenCountOfDescendantsInRange(node->right, x, y);

	// the -1 is so that the element itself is not counted
	int descendantsInRangeCount =
		countDescendantsInRange(node->left, x, y) + countDescendantsInRange(node->right, x, y);

	// Print
	PrintElementAndDescendants(node->data, descendantsInRangeCount, x, y);

	// add to left right sum
	if (descendantsInRangeCount % 2 == 0 && descendantsInRangeCount != 0)
		return leftSum + rightSum + node->data;
	else
		return leftSum + rightSum;
}
