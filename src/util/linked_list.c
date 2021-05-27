//
// Created by timti on 27/05/2021.
//

#include "EUL/util/linked_list.h"
#include "stdlib.h"

LinkedList_t *ll_create()
{
    LinkedList_t *list = malloc(sizeof(LinkedList_t));
    list->head = 0x00;
    list->size = 0;
    return list;
}

void ll_add(LinkedList_t *list, char *value)
{
    struct ListNode* node = malloc(sizeof(struct ListNode));
    node->value = value;
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