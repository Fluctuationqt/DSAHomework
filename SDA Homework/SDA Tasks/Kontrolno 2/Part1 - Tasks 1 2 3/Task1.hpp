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

/* vrushta broq na elementite koito sa v obhvata [x, y] za edno durvo
naprimer
3
1 2

=> 3 ako x = 1, y = 3
=> 2 ako x = 1, y = 2
=> 1 ako x = 1, y =1
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

// task1 solution ( uslovieto e vuv papkata na proekta
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

/*
a)
[4, 6] => {4,5,6}
6 -> 1 naslednik ot intervala
4 -> 2 naslednik ot intervala
8 -> 3 naslednik ot intervala
=> Sumata e 4

b)
[4, 10] => {4,5,6,7,8,9,10}
LPD:
6 -> 2 naslednik ot intervala
4 -> 3 naslednik ot intervala
DPD:
10 -> 1 naslednik ot intervala
12 -> 2 naslednika ot intervala
Root:
8 -> 4 naslednika ot intervala vlqvo i 2 naslednika otdqsno => 6 naslednika v intervala
=> Sumata e 6+12+8=26
*/