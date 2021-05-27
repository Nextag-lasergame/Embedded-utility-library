//
// Created by timti on 27/05/2021.
//

#include "linked_list_test.h"
#include <EUL/EUL.h>
#include <unity.h>
#include "string.h"

void llCreateCalledSuccessfully_returnsLinkedList();
void llAddCalledSuccessfully_addsToLinkedList();
void llRemoveIndexCalledSuccessfully_returnsTrue();
void llRemoveIndexCalledIndexOutOfBounds_returnsFalse();
void llGetSizeCalledSuccessfully_returnsSize();
void llGetIndexCalledSuccessfully_returnsValue();
void llGetIndexCalledIndexOutOfBounds_returnsNull();

void linked_list_test()
{
    RUN_TEST(llCreateCalledSuccessfully_returnsLinkedList);
    RUN_TEST(llAddCalledSuccessfully_addsToLinkedList);
    RUN_TEST(llRemoveIndexCalledSuccessfully_returnsTrue);
    RUN_TEST(llRemoveIndexCalledIndexOutOfBounds_returnsFalse);
    RUN_TEST(llGetSizeCalledSuccessfully_returnsSize);
    RUN_TEST(llGetIndexCalledSuccessfully_returnsValue);
    RUN_TEST(llGetIndexCalledIndexOutOfBounds_returnsNull);
}

void llCreateCalledSuccessfully_returnsLinkedList()
{
    LinkedList_t *list = ll_create();
    TEST_ASSERT_NOT_NULL_MESSAGE(list, "Method ll_create returned null");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, list->size, "List size is not equal to 0");
    TEST_ASSERT_NULL_MESSAGE(list->head, "The linked list head is not null");
    ll_delete(list);
}

void llAddCalledSuccessfully_addsToLinkedList()
{
    LinkedList_t *list = ll_create();

    ll_add(list, "test");
    
    TEST_ASSERT_EQUAL_INT32(1, list->size);
    TEST_ASSERT_NOT_NULL(list->head);
    TEST_ASSERT_EQUAL_STRING("test", list->head->value);

    ll_add(list, "test2");
    TEST_ASSERT_EQUAL_INT32(2, list->size);
    TEST_ASSERT_NOT_NULL(list->head->next);
    TEST_ASSERT_EQUAL_STRING("test2", list->head->next->value);
    ll_delete(list);
}

void llRemoveIndexCalledSuccessfully_returnsTrue()
{
    LinkedList_t *list = ll_create();
    ll_add(list, "test");
    bool result = ll_removeIndex(list, 0);
    TEST_ASSERT_TRUE_MESSAGE(result, "ll_removeIndex returned false");
    TEST_ASSERT_NULL_MESSAGE(list->head, "The list head is not null");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, list->size, "The list size is not 0");
    ll_delete(list);
}

void llRemoveIndexCalledIndexOutOfBounds_returnsFalse()
{
    LinkedList_t *list = ll_create();
    bool result = ll_removeIndex(list, 0);
    TEST_ASSERT_FALSE_MESSAGE(result, "ll_removeIndex returned true");
    ll_delete(list);
}

void llGetSizeCalledSuccessfully_returnsSize()
{
    LinkedList_t *list = ll_create();
    TEST_ASSERT_EQUAL_INT32(0, ll_getSize(list));

    ll_add(list, "test");
    TEST_ASSERT_EQUAL_INT32(1, ll_getSize(list));
    ll_delete(list);
}

void llGetIndexCalledSuccessfully_returnsValue()
{
    LinkedList_t *list = ll_create();

    ll_add(list, "First element");
    ll_add(list, "Second element");

    const char* firstElement = ll_getIndex(list, 0);
    const char* secondElement = ll_getIndex(list, 1);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("First element", firstElement, "The first element is not equal to \"First element\"");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Second element", secondElement, "The first element is not equal to \"Second element\"");

    ll_delete(list);
}

void llGetIndexCalledIndexOutOfBounds_returnsNull()
{
    LinkedList_t *list = ll_create();

    const char* result = ll_getIndex(list, 0);
    TEST_ASSERT_NULL_MESSAGE(result, "ll_getIndex didn't return null");

    ll_delete(list);
}