#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = (struct Link *) malloc(sizeof(struct Link));

	list->size = 0; //Sets list's size to 0.
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	//list->sentinel->value = -1;
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link * newLink = (struct Link *)malloc(sizeof(struct Link));
	newLink->next = NULL; //Set pointers to Null
	newLink->prev = NULL; //Set pointers to Null
	newLink->value = value; //Set value to Value
	return newLink;//Return the new link
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link * newLink = createLink(value); //Create a new Link.
	newLink->next = link->next; //New link's next is link's next
	newLink->prev = link; //New link's preivous is equal to link.
	newLink->next->prev = newLink; //Set the preious link's next to the new link
	newLink->prev->next = newLink; //Set the next link's previous to the new link
	list->size++; //Increase list size by 1.


}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	link->prev->next = link->next; //Link's previous next is now link's next
	link->next->prev = link->prev;//Link's next's previous is now link's previous

	//Free memorr
	link->next = NULL;
	link->prev = NULL;
	free(link);
	link = NULL;
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	struct Link * temp; //Create a temporary Link
	while (!circularListIsEmpty(list))//While the list isn't empty.
	{
		temp = list->sentinel->next; //Temp is sentinel's next.
		removeLink(list, temp); //Remove the link from the list.
	}

	free(list->sentinel); //Free the sentinel
	free(list); //Free list.
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value); //Use add Link After to add link.

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->prev, value); //Use Addlink Afte

}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	return (list->sentinel)->next->value; 
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	return(list->sentinel)->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	if (list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	int size = list->size; //Find the size of the list.
	struct Link * cycle = list->sentinel->next; //Set Link for Cycle to sentinel's next.

	while (size != 0)
	{
		printf("%g ", cycle->value); //Print the Value
		cycle = cycle->next; //Make Cycle the next element
		size--; //Decrease the size of the function
	}
	printf("\n"); //Clear the Line

}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	struct Link * cycle = list->sentinel; //Create a Link to hold hte sentinel.
	int i = 0; //Create integer for for loop.


	for (i = 0; i < list->size + 1; i++)
	{
		struct Link *temp = cycle->next; //Link to hold temporary and set to first link
		cycle->next = cycle->prev; //Set current to the previous.

		cycle->prev = temp; //Set current's previous to the next.

		cycle = cycle->next;//Traverse to hte next node.
	}
}