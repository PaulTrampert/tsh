#include "./list.h"
#include "exit_codes.h"
#include <stdlib.h>

struct _list_node
{
    void *data;
    struct _list_node *next;
    struct _list_node *prev;
};

typedef struct _list_node ListNode;

struct _list
{
    ListNode *head;
    ListNode *tail;
    size_t size;
};

struct _listIterator
{
    List *list;
    ListNode *current;
};

ListNode *list_node_create(void *data);
void list_insert_before(ListNode *before, ListNode *new_node);
void list_insert_after(ListNode *after, ListNode *new_node);

void list_insert_before(ListNode *before, ListNode *new_node)
{
    ListNode *after = before->prev;
    after->next = new_node;
    new_node->prev = after;
    new_node->next = before;
    before->prev = new_node;
}

void list_insert_after(ListNode *after, ListNode *new_node)
{
    list_insert_before(after->next, new_node);
}

ListNode *list_node_create(void *data)
{
    ListNode *node = malloc(sizeof(ListNode));
    if (!node)
        exit(EOOM);

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

List *list_create()
{
    List *list = malloc(sizeof(List));
    if (!list)
        exit(EOOM);

    list->size = 0;
    list->head = list_node_create(NULL);
    if (!list->head)
    {
        free(list);
        exit(EOOM);
    }
    list->tail = list_node_create(NULL);
    if (!list->tail)
    {
        free(list->head);
        free(list);
        exit(EOOM);
    }

    list->head->next = list->tail;
    list->tail->prev = list->head;

    return list;
}

void list_destroy(List *list)
{
    if (!list)
        return;

    ListNode *current = list->head;
    while (current)
    {
        ListNode *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int list_append(List *list, void *data)
{
    if (!list)
        return -1;

    ListNode *new_node = list_node_create(data);
    if (!new_node)
        return -1;

    list_insert_before(list->tail, new_node);
    list->size++;

    return 0;
}

void *list_get(List *list, size_t index)
{
    if (!list || index >= list->size)
        return NULL;

    ListNode *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current ? current->data : NULL;
}

size_t list_size(List *list)
{
    return list ? list->size : 0;
}

void *list_dequeue(List *list)
{
    if (!list || list->size == 0)
        return NULL;

    ListNode *first = list->head->next;
    void *data = first->data;
    list->head->next = first->next;
    first->next->prev = list->head;
    free(first);
    list->size--;

    return data;
}

void *list_head(List *list)
{
    if (!list || list->size == 0)
        return NULL;

    return list->head->next->data;
}

int list_for_each(List *list, int (*callback)(void *data, void *ctx), void *ctx)
{
    if (!list || !callback)
        return -1;

    ListNode *current = list->head->next;
    while (current != list->tail)
    {
        if (callback(current->data, ctx) != 0)
        {
            return -1;
        }
        current = current->next;
    }

    return 0;
}

ListIterator *list_iterator_create(List *list)
{
    if (!list)
        return NULL;

    ListIterator *iter = malloc(sizeof(ListIterator));
    if (!iter)
        exit(EOOM);

    iter->current = list->head->next;
    iter->list = list;

    return iter;
}

void list_iterator_destroy(ListIterator *iter)
{
    free(iter);
}

bool list_iterator_has_next(ListIterator *iter)
{
    if (!iter)
        return false;
    return iter->current != iter->list->tail;
}

void *list_iterator_next(ListIterator *iter)
{
    if (!iter || !list_iterator_has_next(iter))
        return NULL;

    void *data = iter->current->data;
    iter->current = iter->current->next;

    return data;
}
