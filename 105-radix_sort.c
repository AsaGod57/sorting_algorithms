#include "sort.h"
#include <stdlib.h>

/**
 * init_bucket_count - Starts to reset bucket_count values to 0
 * @bucket_count: Specifies array containing  members for arrays in `buckets`
 */
void init_bucket_count(int *bucket_count)
{
	int i;

	for (i = 0; i < 10; i++)
		bucket_count[i] = 0;
}

/**
 * build_buckets - Starts to allocate space for arrays to be held in `buckets`
 * @buckets: Specifies array each containing sorted members of `array`
 * @bucket_count: Specifies array containing  members for arrays in `buckets`
 */
void build_buckets(int *bucket_count, int **buckets)
{
	int *bucket;
	int i;

	for (i = 0; i < 10; i++)
	{
		bucket = malloc(sizeof(int) * bucket_count[i]);
		if (!bucket)
		{
			for (; i > -1; i--)
				free(buckets[i]);
			free(buckets);
			exit(EXIT_FAILURE);
		}
		buckets[i] = bucket;
	}
	init_bucket_count(bucket_count);
}

/**
 * find_max - Starts to search array of integers for highest value
 * @array: Specifies array of values to be searched
 * @size: Specifies number of elements in array
 * Return: The largest integer stored in array (Ends)
 */
int find_max(int *array, size_t size)
{
	int max;
	size_t i;

	max = array[0];
	for (i = 1; i < size; i++)
		if (array[i] > max)
			max = array[i];
	return (max);
}

/**
 * into_array - Converts buckets into array sorted by current digit place
 * @array: Specifies array of values to be printed
 * @size: Specifies number of elements in array
 * @buckets: Specifies array containing sorted members of `array`
 * @bucket_count: Specifies array containing  members for arrays in `buckets`
 */
void into_array(int *array, size_t size, int **buckets, int *bucket_count)
{
	int i, j, k;

	/* flatten bucket members in order into array sorted by place */
	for (k = 0, i = 0; k < 10; k++)
	{
		for (j = 0; j < bucket_count[k]; j++, i++)
			array[i] = buckets[k][j];
	}
	/* print results */
	print_array(array, size);
	/* free buckets from current pass */
	for (i = 0; i < 10; i++)
		free(buckets[i]);
}

/**
 * radix_sort - Sorts array of integers in ascend order using a Radix sort
 * @array: Specifies array of values to be sorted
 * @size: Specifies number of elements in array
 */
void radix_sort(int *array, size_t size)
{
	int **buckets;
	int bucket_count[10];
	int max, max_digits, pass, divisor, digit;
	size_t i;

	if (!array || size < 2)
		return;
	buckets = malloc(sizeof(int *) * 10);
	if (!buckets)
		exit(1);
	/* find amount of places in largest element */
	max = find_max(array, size);
	for (max_digits = 0; max > 0; max_digits++)
		max /= 10;
	/* one sorting pass for each place in max_digits */
	for (pass = 0, divisor = 1; pass < max_digits; pass++, divisor *= 10)
	{
		init_bucket_count(bucket_count);
		/* find amount of members in each bucket */
		for (i = 0; i < size; i++)
		{
			digit = (array[i] / divisor) % 10;
			bucket_count[digit]++;
		}
		build_buckets(bucket_count, buckets);
		/* fill buckets sorting by digit at current power of 10 */
		for (i = 0; i < size; i++)
		{
			/* find digit of source element at that power of 10 */
			digit = (array[i] / divisor) % 10;
			/* place member of source array in digit's bucket */
			buckets[digit][bucket_count[digit]] = array[i];
			/* record increase in bucket fill level */
			bucket_count[digit]++;
		}
		into_array(array, size, buckets, bucket_count);
	}
	free(buckets);
}
