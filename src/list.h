#include <stddef.h>
#ifndef LIST_H
#define LIST_H

struct _list_node {
    void *data;
    struct _list_node *next;
    struct _list_node *prev;
};

typedef struct _list_node ListNode;

struct _list {
    ListNode *head;
    ListNode *tail;
    size_t size;
};

typedef struct _list List;

List *list_create();
void list_destroy(List *list);
int list_append(List *list, void *data);
void *list_get(List *list, size_t index);
void *list_dequeue(List *list);
size_t list_size(List *list);

#endif // LIST_H