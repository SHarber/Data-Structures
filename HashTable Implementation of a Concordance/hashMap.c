/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: Sarah
 * Date: 03/10/17
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
	int i; //Variable for for loop.
	for (i = 0; i < map->capacity; i++)
	{
		HashLink * newLink = map->table[i]; //Create link to store the table index
		map->table[i] = NULL; // Make link = NULL

		while (newLink != NULL) //While link is not equal to null.
		{
			HashLink *temp = newLink; //Create a temp HashLink and store newLink/
			newLink = newLink->next; //NewLink is equal to the next link.
			hashLinkDelete(temp); //Delete the temp link.
		}
		free (map->table[i]); //Free map's table index.
	}
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
	int index = HASH_FUNCTION(key) % (map->capacity); //Use hash function & the index of the linked list to find the index

	HashLink * newLink = map->table[index];  //Store the map's table at index in a new link.

	while (newLink != NULL) //While newLink is not null.
	{
		if (strcmp(newLink->key, key) == 0)
			return &(newLink->value); // If link matches treutrn pointer
		newLink = newLink->next; // newLink=newLink->next
	}
	return NULL; //Otherwise return null
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	int i= 0;
	HashLink * newLink;
	int oCapacity = map->capacity; //Store the old capacity
	HashLink **oTable = map->table; //Store the old table in new table.
	hashMapInit(map, capacity);  //Initiatlize new map with the new capacity
	for (i = 0; i < oCapacity; i++) //For loop to rehash table.
	{
		newLink = oTable[i];
		while (newLink != NULL)
		{
			hashMapPut(map, newLink->key, newLink->value);
			newLink = newLink->next; // Link is now next link
		}
	}

	for (i = 0; i < oCapacity; i++) //For loop to clear data of old table.
	{
		newLink = oTable[i];
		oTable[i] = NULL;

		while (newLink != NULL)
		{
			HashLink * temp = newLink;
			newLink = newLink->next;
			hashLinkDelete(temp); //Delete temp
		}
		free(oTable[i]); //free oTable index
	}
	free(oTable);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
	if (hashMapTableLoad(map) >= MAX_TABLE_LOAD) //Check to see if hashmap needs to be resized
	{
		resizeTable(map, 2 * map->capacity); //If so, resize table to double size.
	}

	int index = HASH_FUNCTION(key) % (map->capacity); //Find the index
	if (index < 0)  //if index is less than 0.
		index += map->capacity; //Add map's capacity to the index.
	
	HashLink* link = map->table[index]; //Link is equal to the link at the index
	HashLink* newLink = NULL; 

	if (link == NULL) //If the link is empty
	{
		newLink = hashLinkNew(key, value, NULL); //Create a new Link in newLink
		map->table[index] = newLink; //Store new link at indexed empty bucket
		map->size++; //Increase the map's size.
	}
	else
	{
		while (link != NULL) // While not empty
		{

			if (strcmp(link->key, key) == 0) //Compare the keys
			{
				link->value = value; //Link's value is value.
				return; //return
			}

			link = link->next; //Link is equal to link's next.
		}

		newLink = hashLinkNew(key, value, map->table[index]); //Otherwsie create new link.
		map->table[index] = newLink;
		map->size++;
		return;

	}

}


/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
	if(hashMapContainsKey(map, key))
{
	
		

	int index = HASH_FUNCTION(key) % (map->capacity); // Get index

	HashLink* current = map->table[index];
	HashLink* last = map->table[index];

	if (current == NULL)
		return;

	while (current != NULL) //While not equal to null
	{
		if (strcmp(current->key, key) == 0) //cmp keys.
		{
			if (current == map->table[index])//If current is equal to the index
			{
				map->table[index] = current->next;//the index is equal to curren'ts next.
				hashLinkDelete(current); //delete current
				map->size--; //decrease size
				current = 0; //current is now equal to 0.
			}
			else //otherwise
			{
				last->next = current->next; //Last's next is equal to current'ls next
				hashLinkDelete(current); //Delete current
				map->size--; //decrase size
				current = 0; //current is qual to 0.
			}
		}
		else //if keys are not == 0
		{
			last = current; //Last is equal to current.
			current = current->next; //Current is equal to curren'ts next.
		}


	}
}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
	int index = HASH_FUNCTION(key) % (map->capacity); //Search for index.

	HashLink* newLink = map->table[index]; //Link is eual to index

	while (newLink != NULL) {
		if (strcmp(newLink->key, key) == 0) 
		{
			return 1; // if key is found return 1
		}
		newLink = newLink->next;
	}

	return 0; //If not found return 0.
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
	int numEmpty = 0; //Initialize number of empty buckets to 0.
	for (int i = 0; i < map->capacity; i++) //Loop through the map
	{
		HashLink * newLink = map->table[i];
		if (newLink == NULL) //If link is == Null (empty)
			numEmpty++; //Increase num empty by 1
	}

	return numEmpty; //Return number of empty buckets.
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
	float numLinks = (float)map->size;
	float numBuckets = (float)map->capacity;
	return (numLinks / numBuckets); //return the division of numlinks & numbuckets
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
