#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * PrintArray - Starts to print array of integers for range of indicies
 * @array: Specifies array of values to be printed
 * @iBeg: Specifies starting index value
 * @iEnd: Specifies ending index value
 */
void PrintArray(int *array, int iBeg, int iEnd)
{
	int i;

	for (i = iBeg; i < iEnd; i++)
		if (i < iEnd - 1)
			printf("%i, ", array[i]);
		else
			printf("%i\n", array[i]);
}

/**
 * CopyArray - Starts simple 1 for 1 copy of source[] to dest[]
 * @source: Specifies array of values to be sorted
 * @iBeg: Specifies starting index value
 * @iEnd: Specifies ending index value
 * @dest: Specifies array to store sorted integers
 */
void CopyArray(int *source, int iBeg, int iEnd, int *dest)
{
	int i;

	for (i = iBeg; i < iEnd; i++)
		dest[i] = source[i];
}

/**
 * TopDownMerge - Starts to sort subsections
 * @source: Specifies array of values to be sorted
 * @iBeg: Specifies left run starting index value
 * @iMid: Specifies right run starting index value
 * @iEnd: Specifies right run ending index value
 * @dest: Specifies array to store sorted integers
 */
void TopDownMerge(int *source, int iBeg, int iMid, int iEnd, int *dest)
{
	int i, j, k;

	i = iBeg, j = iMid;

	printf("Merging...\n");
	printf("[left]: ");
	PrintArray(source, iBeg, iMid);
	printf("[right]: ");
	PrintArray(source, iMid, iEnd);
	/* While there are elements in the left or right runs... */
	for (k = iBeg; k < iEnd; k++)
	{
		/* If left run head exists and is <= existing right run head */
		if (i < iMid && (j >= iEnd || source[i] <= source[j]))
		{
			dest[k] = source[i];
			i++;
		}
		else
		{
			dest[k] = source[j];
			j++;
		}
	}
	printf("[Done]: ");
	PrintArray(dest, iBeg, iEnd);
}

/**
 * TopDownSplitMerge - Starts recursive engine of merge_sort
 * @source: Specifies array of integers to be sorted
 * @iBeg: Specifies starting index value
 * @iEnd: Specifies ending index value
 * @dest: Specifies array to store sorted integers
 */
void TopDownSplitMerge(int *source, int iBeg, int iEnd, int *dest)
{
	int iMid;

	if (iEnd - iBeg < 2) /* if run size == 1 */
		return;     /* consider it sorted */
	/* split the run longer than 1 item into halves */
	iMid = (iEnd + iBeg) / 2;

	TopDownSplitMerge(dest, iBeg, iMid, source);  /* sort left run */
	TopDownSplitMerge(dest, iMid, iEnd, source);  /* sort right run */
	/* merge the resulting runs from array[] into work_copy[] */
	TopDownMerge(source, iBeg, iMid, iEnd, dest);
}

/**
 * merge_sort - Starts to sort an array of integers
 * @array: Specifies array of integers to be sorted
 * @size: Specifies amount of elements in array
 */
void merge_sort(int *array, size_t size)
{
	int *work_copy;

	if (!array || size < 2)
		return;

	work_copy = malloc(sizeof(int) * size);
	if (!work_copy)
		return;

	CopyArray(array, 0, size, work_copy);
	TopDownSplitMerge(work_copy, 0, size, array);

	free(work_copy);
}
