//
// Created by timti on 27/05/2021.
//

#ifndef EMBEDDED_UTILITY_LIBRARY_LINKED_LIST_H
#define EMBEDDED_UTILITY_LIBRARY_LINKED_LIST_H

#include <inttypes.h>
#include "stdbool.h"

/**
 * @brief Struct defining a linked list node
 */
struct ListNode
{
    struct ListNode *next;
    const char *value;
};

/**
 * @brief Struct defining the linked list. This struct is not meant to be edited by the user.
 */
typedef struct
{
    struct ListNode *head;
    uint32_t size;
} LinkedList_t;

/**
 * @brief Creates a new linked list.
 * @return A pointer to the created linked list
 */
LinkedList_t *ll_create();

/**
 * @brief Adds a value to a linked list. The list parameter can't be equal to 0x00
 * @param list The list  to add to
 * @param value The value to add
 */
void ll_add(LinkedList_t *list, const char *value);

/**
 * @brief Removes a specific node, identified with the index, from the linked list. The index can't be bigger then the size of the linked list
 * @param list The list to remove from
 * @param index The index of the node to remove
 * @return Wether the remove was successful
 */
bool ll_removeIndex(LinkedList_t *list, uint32_t index);

/**
 * @brief Gets the size of the list
 * @param list The list to get the size of
 * @return The size
 */
uint32_t ll_getSize(LinkedList_t *list);

/**
 * @brief Gets the value from a specific index in the list. The index can't be bigger then the size of the linked list
 * @param list The list to read from
 * @param index The index to read
 * @return The read value
 */
const char *ll_getIndex(LinkedList_t *list, uint32_t index);

/**
 * @brief Deletes the list, including all contents.
 * @param list The list to delete
 */
void ll_delete(LinkedList_t *list);

#endif //EMBEDDED_UTILITY_LIBRARY_LINKED_LIST_H
