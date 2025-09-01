#include <stddef.h>
#include <stdbool.h>
#ifndef LIST_H
#define LIST_H

typedef struct _list List;

typedef struct _listIterator ListIterator;

List *list_create();
void list_destroy(List *list);
int list_append(List *list, void *data);
void *list_get(List *list, size_t index);
void *list_dequeue(List *list);
void *list_head(List *list);
size_t list_size(List *list);
int list_for_each(List *list, int (*callback)(void *data, void *ctx), void *ctx);

ListIterator *list_iterator_create(List *list);
void list_iterator_destroy(ListIterator *iter);
bool list_iterator_has_next(ListIterator *iter);
void *list_iterator_next(ListIterator *iter);
#endif // LIST_H