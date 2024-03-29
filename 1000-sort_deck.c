#include "deck.h"
#include <stdio.h>

/**
 *_strcmp - Starts to compare two strings
 *@str1: Specifies first string
 *@str2: Specifies second string
 *Return: 1 when  str1 and str2 are  equal, 0 if otherwise (Ends)
 */
int _strcmp(const char *str1, char *str2)
{
	size_t i = 0;

	if (str1 == '\0')
		return (0);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '\0' && str2[i])
		return (0);
	return (1);
}
/**
 * get_card_position - Displays the position based on card entered
 * @node: Specifies  the card
 * Return: The card position (Ends)
 */
int get_card_position(deck_node_t *node)
{
	int value;

	value = (*node).card->value[0] - '0';
	if (value < 50 || value > 57)
	{
		if (_strcmp((*node).card->value, "Ace") == 1)
			value = 1;
		else if (_strcmp((*node).card->value, "10") == 1)
			value = 10;
		else if (_strcmp((*node).card->value, "Jack") == 1)
			value = 11;
		else if (_strcmp((*node).card->value, "Queen") == 1)
			value = 12;
		else if (_strcmp((*node).card->value, "King") == 1)
			value = 13;
	}
	value += (*node).card->kind * 13;
	return (value);
}
/**
 *swap_card - Starts to swap a card for previous one
 *@card: Specifies card
 *@deck: Specifies card deck
 *Return: The  pointer to a card (Ends)
 */
deck_node_t *swap_card(deck_node_t *card, deck_node_t **deck)
{
	deck_node_t *back = card->prev, *current = card;
	/*NULL, 19, 48, 9, 71, 13, NULL*/

	back->next = current->next;
	if (current->next)
		current->next->prev = back;
	current->next = back;
	current->prev = back->prev;
	back->prev = current;
	if (current->prev)
		current->prev->next = current;
	else
		*deck = current;
	return (current);
}

/**
 * insertion_sort_deck - Starts function that sorts a doubly linked deck
 * @deck: Specifies dobule linked deck to sort
 */
void insertion_sort_deck(deck_node_t **deck)
{
	int value_prev, value_current;
	deck_node_t *node;

	if (deck == NULL || (*deck)->next == NULL)
		return;
	node = (*deck)->next;
	while (node)
	{
		/* preparing the previous value */
		if (node->prev)
		{
			value_prev = get_card_position((node->prev));
			value_current = get_card_position(node);
		}
		while ((node->prev) && (value_prev > value_current))
		{
			value_prev = get_card_position((node->prev));
			value_current = get_card_position(node);
			node = swap_card(node, deck);

		}
		node = node->next;
	}
}
/**
 * sort_deck - Starts to sort a deck using insertion sort algorithm
 * @deck: Specifies deck
 */
void sort_deck(deck_node_t **deck)
{
	insertion_sort_deck(deck);
}
