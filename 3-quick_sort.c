#include "sort.h"

/**
*swap - Convert the positions of two elements into an array
*@array: Specifies array
*@item1: Specifies first array element
*@item2: Specifies second array element
*/
void swap(int *array, ssize_t item1, ssize_t item2)
{
	int tmp;

	tmp = array[item1];
	array[item1] = array[item2];
	array[item2] = tmp;
}
/**
 *lomuto_partition - Starts lomuto partition sorting scheme implementation
 *@array: Specifies array
 *@first: Specifies first array element
 *@last: Specifies last array element
 *@size: Specifies array size
 *Return: The position of the last element sorted (Ends)
 */
int lomuto_partition(int *array, ssize_t first, ssize_t last, size_t size)
{
	int pivot = array[last];
	ssize_t current = first, finder;

	for (finder = first; finder < last; finder++)
	{
		if (array[finder] < pivot)
		{
			if (array[current] != array[finder])
			{
				swap(array, current, finder);
				print_array(array, size);
			}
			current++;
		}
	}
	if (array[current] != array[last])
	{
		swap(array, current, last);
		print_array(array, size);
	}
	return (current);
}
/**
 *qs - Starts quicksort algorithm implementation
 *@array: Specifies array
 *@first: Specifies first array element
 *@last: Specifies last array element
 *@size: Specifies array size
 */
void qs(int *array, ssize_t first, ssize_t last, int size)
{
	ssize_t position = 0;


	if (first < last)
	{
		position = lomuto_partition(array, first, last, size);

		qs(array, first, position - 1, size);
		qs(array, position + 1, last, size);
	}
}
/**
 *quick_sort - Starts to prepare the terrain to quicksort algorithm
 *@array: Specifies array
 *@size: Specifies array size
 */
void quick_sort(int *array, size_t size)
{
	if (!array || size < 2)
		return;
	qs(array, 0, size - 1, size);
}
