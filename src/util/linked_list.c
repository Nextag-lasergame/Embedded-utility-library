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

void ll_add(LinkedList_t *list, const char *value)
{

}

bool ll_removeIndex(LinkedList_t *list, uint32_t index)
{
    return false;
}

uint32_t ll_getSize(LinkedList_t *list)
{
    return 0;
}

const char *ll_getIndex(LinkedList_t *list, uint32_t index)
{
    return 0x00;
}

void ll_delete(LinkedList_t *list)
{

}