#ifndef DECK_H
#define DECK_H

/**
 * enum kind_e - Displays card kind
 * @SPADE: Specifies spade kind
 * @HEART: Specifies heart kind
 * @CLUB: Specifies club kind
 * @DIAMOND: Specifies diamond kind
 */
typedef enum kind_e
{
	SPADE = 0,
	HEART,
	CLUB,
	DIAMOND
} kind_t;

/**
 * struct card_s - Starts playing card
 * @value: Specifies value of the card
 * @kind: Specifies kind of the card
 */
typedef struct card_s
{
	const char *value;
	const kind_t kind;
} card_t;

/**
 * struct deck_node_s - Displays deck of card
 * @card: Specifies pointer to the card of the node
 * @prev: Specifies pointer to the previous node of the list
 * @next: Specifies pointer to the next node of the list
 */
typedef struct deck_node_s
{
	const card_t *card;
	struct deck_node_s *prev;
	struct deck_node_s *next;
} deck_node_t;

void sort_deck(deck_node_t **deck);
#endif /* DECK_H */
