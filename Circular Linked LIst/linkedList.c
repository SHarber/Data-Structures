#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this

	struct Link * front = (struct Link *) malloc(sizeof(struct Link)); //Allocate a new Link for the beginning.
	assert(front != 0); //Assert it is not null

	struct Link * back = (struct Link *) malloc(sizeof(struct Link)); //Allocate a new Link for the end.
	assert(back != 0);//Assert it is not null.

	
	front->next = NULL; //Front's  next is Null.
	front->prev = back; //Front's previous is the back
	back->next = front; //Back's next is front.
	back->prev = NULL; //Back's prev is equal to Null.

	list->frontSentinel = front; //Front Sentinel is set to the beginning
	list->backSentinel = back; //Back Sentinel is set to the back.
	list->size = 0; //Size fo the List is set to 0.
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	struct Link * newLink = (struct Link*)malloc(sizeof(struct Link)); //Create a newLink

	struct Link * previousLink; //Create a link for the previous Link.
	previousLink = link->prev; //Save the previous link to link.
	
	link->prev = newLink; //Link's new previous is the new link.
	previousLink->next = newLink; //Previous Links next is now the new link
	
	newLink->prev = previousLink; //newLink's previous is the previous link.
	newLink->next = link; // newLink's next is link.
	newLink->value = value; //newLink's value is the value passed.

	list->size++; //Increase the size of the list by 1.	
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list->size != 0); //Assert that the size of the list is not 0.

	struct Link * linkToDelete = link; //Save link to be deleted
	struct Link * linkBehindDeleted = link->prev; //Save link behind deleted
	struct Link * linkInFrontOfDeleted = link->next; //Save link in front of the Deleted.

	linkBehindDeleted->next = linkInFrontOfDeleted; //Set the link behind's new next.
	linkInFrontOfDeleted->prev = linkBehindDeleted; //Set the link in front's new prev.

	link->next = NULL; //Set pointer to NULL
	link->prev = NULL; //Set Pointer to NULL
	free(linkToDelete); //Delete the link

	list->size--; //Decrease the size of the link.
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	struct Link *newLink = (struct Link *)malloc(sizeof(struct Link));//Create a new Link
	struct Link * oldFront = list->frontSentinel->prev; //Make front Sentinel's old previous be stored in new variable
	oldFront->next = newLink; //New Link is now the front.
	list->frontSentinel->prev = newLink;//Assign a new front.
	newLink->next = list->frontSentinel; //Front Sentinel is now newLink(fronts) front.
	newLink->prev = oldFront; //NewLink's previous is the old front.
	newLink->value = value; //Assign the newLink its value
	list->size++;//Increase Link Size.
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	struct Link *newLink = (struct Link *)malloc(sizeof(struct Link));//Create a new Link
	struct Link * oldBack = list->backSentinel->next; //Make front Sentinel's old back be stored in new variable
	oldBack->prev = newLink; //Old Link is now the back.
	list->backSentinel->next = newLink;//Assign a new back.
	newLink->prev = list->backSentinel; //Front Sentinel is now newLink(fronts) front.
	newLink->next = oldBack; //NewLink's previous is the old front.
	newLink->value = value; //Assign the newLink its value
	list->size++;//Increase Link Size.

}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list->size != 0); //Assert taht the list is not empty
	return list->frontSentinel->prev->value;//Return the front's value.
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list->size != 0); //Assert that list is not empty
	return list->backSentinel->next->value;//Return the back value
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list->size != 0); //Assert tha the list is not empty

	struct Link * remove = list->frontSentinel->prev; //Set link to be removed
	struct Link * newFront = list->frontSentinel->prev->prev; //Create the New Front
	newFront->next = list->frontSentinel; //New front's Next is the front sentinel.
	list->frontSentinel->prev = newFront;//New front is now front Sentinel's front

	remove->prev = NULL; //set remove pointers to Null
	remove->next = NULL; //set remove pointers to Null
	free(remove); //Free memory allocated to remove
	remove = NULL;//Set to NULL
	list->size--;//Decrease size of link listed.

}


/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list->size != 0); //Assert tha the list is not empty

	struct Link * remove = list->backSentinel->next; //Set link to be removed
	struct Link * newBack = list->backSentinel->next->next; //Create the New Front

	newBack->prev = list->backSentinel; //Make newBack's prev = back sentinal
	list->backSentinel->next = newBack; //Make backSentinel's next = new back.

	remove->next = NULL; //Set next to Null
	remove->prev = NULL; //Set prev to Null
	free(remove); //Free Memory.
	remove = NULL; //set to Null
	
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	if (list->size != 0)
		return 0;
	else
		return 1;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list->size != 0); //Assert list is not empty
	struct Link * linkToPrint = list->frontSentinel->prev; //set link to print to first link.
	//Create a do-loop to cycle through list.
	do {
		printf("%d ", linkToPrint->value); //Print the Value
		linkToPrint = linkToPrint->prev; //Move to the prev Link
	} while (linkToPrint->prev != 0); //Continuee while not null.
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	linkedListAddBack(list, value); //Add value to the back of list
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list->size != 0); //Assert that the list is not empty
	struct Link * currentLink = list->frontSentinel->prev; //Set current Link to first Link.
	
	//Create a do loop to determine if the element is in the bag.
	do {
		if (currentLink->value == value)
			return 1; //If the current Link's value is equal to the value to be searched return 1
		currentLink = currentLink->prev;
	} while (currentLink != 0);

	return 0; //If not found retun 0.
	
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list->size != 0); //Assert that list is not empty
	assert(linkedListContains(list, value) != 0);
	struct Link * currentLink = list->frontSentinel->prev; //Set current Link to first link
	
	do { //Create do loop to find the link.

		if (currentLink->value == value) //If the current link's value is equal to the value.
		{
			currentLink->next->prev = currentLink->prev; //Make the next links previous to the current links previous
			currentLink->prev->next = currentLink->next;// Make the previous link's next to current link's next.
			currentLink->next = NULL; //Set pointer to Null
			currentLink->prev = NULL; //Set pointer to Null;
			free(currentLink); //Free memory
			list->size--; //Decrease list's size by 1.
			return;//Stop loop
		}
		currentLink = currentLink->prev;//Make current Link the next link.
	} while (currentLink != 0);

}
