/*
 * Copyright (c) 2020-2021 Tim Herreijgers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "EUL/util/linked_list.h"
#include "stdlib.h"
#include "string.h"

/**
 * @brief Struct defining a linked list node
 */
struct ListNode
{
    struct ListNode *next;
    char *value;
};

/**
 * @brief Struct defining the linked list. This struct is not meant to be edited by the user.
 */
typedef struct linkedList
{
    struct ListNode *head;
    uint32_t size;
} LinkedList_t;

LinkedList_t *ll_create()
{
    LinkedList_t *list = malloc(sizeof(LinkedList_t));
    list->head = 0x00;
    list->size = 0;
    return list;
}

void ll_add(LinkedList_t *list, const char *value)
{
    struct ListNode* node = malloc(sizeof(struct ListNode));
    node->value = malloc(strlen(value) * sizeof(char) + 1);
    memcpy(node->value, value, strlen(value) * sizeof(char) + 1);
    node->next = 0x00;

    if(list->size == 0)
    {
        list->head = node;
        list->size = 1;
        return;
    }

    struct ListNode* current = list->head;

    while(current->next != NULL)
    {
        current = current->next;
    }

    current->next = node;
    list->size++;
}

bool ll_removeIndex(LinkedList_t *list, uint32_t index)
{
    if (index >= list->size)
        return false;

    struct ListNode *last = list->head;
    struct ListNode *current = list->head;

    for (uint32_t i = 0; i < index; i++)
    {
        last = current;
        current = current->next;
    }

    struct ListNode *next = current->next;
    free(current->value);
    free(current);

    if (index == 0)
        list->head = next;
    else
        last->next = next;

    list->size--;

    return true;
}

uint32_t ll_getSize(LinkedList_t *list)
{
    return list->size;
}

const char *ll_getIndex(LinkedList_t *list, uint32_t index)
{
    if (index >= list->size)
        return NULL;

    struct ListNode* current = list->head;

    for(uint32_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->value;
}

void ll_delete(LinkedList_t *list)
{
    struct ListNode *next = list->head;
    struct ListNode *current = NULL;
    while(next != NULL)
    {
        current = next;
        next = current->next;

        free(current->value);
        free(current);
    }
    free(list);
}