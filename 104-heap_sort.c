#include "sort.h"

/**
 * iParent - Displays index of parent node for an array arranged
 * @i: Specifies  index to determine parent node index
 * Return: The index of parent node (Ends)
 */
int iParent(int i)
{
	return ((i - 1) / 2);
}

/**
 * iLeftChild- Displays index of left child branch for an array
 * @i: Specifies index to determine left child branch index
 * Return: The index of left child node (Ends)
 */
int iLeftChild(int i)
{
	return ((2 * i) + 1);
}

/**
 * ConvertToHeap - Stars to arrange array of integers into a heap tree
 * @array: Specifies array of integers
 * @size: Specifies number of elements in array
 */
void ConvertToHeap(int *array, size_t size)
{
	int start;

	start = iParent(size - 1);

	while (start >= 0)
	{
		SiftDown(array, size, start, size - 1);
		start--;
	}
}

/**
 * SiftDown - Starts to shuffle heap tree sorted array into array sorted
 * @array: Specifies array of values to be sorted in place
 * @size: Specifies number of elements in array
 * @start: Specifies starting index
 * @end: Specifies ending index
 */
void SiftDown(int *array, size_t size, int start, int end)
{
	int root, swap, temp, child;

	root = start;

	while (iLeftChild(root) <= end)
	{
		child = iLeftChild(root);
		swap = root;

		if (array[swap] < array[child])
			swap = child;
		if (child + 1 <= end && array[swap] < array[child + 1])
			swap = child + 1;
		if (swap != root)
		{
			temp = array[root];
			array[root] = array[swap];
			array[swap] = temp;
			print_array(array, size);
			root = swap;
		}
		else
			return;
	}
}

/**
 * heap_sort - Starts to sort array of integers in ascending order
 * @array: Specifies array of values to be sorted
 * @size: Specifies number of elements in array
 */
void heap_sort(int *array, size_t size)
{
	int iEnd, temp;

	if (!array || size < 2)
		return;

	ConvertToHeap(array, size);

	iEnd =  (int)size - 1;
	while (iEnd > 0)
	{
		temp = array[iEnd];
		array[iEnd] = array[0];
		array[0] = temp;
		print_array(array, size);
		iEnd--;
		SiftDown(array, size, 0, iEnd);
	}
}
