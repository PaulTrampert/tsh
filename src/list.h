#include <stddef.h>
#ifndef LIST_H
#define LIST_H

typedef struct _list List;

List *list_create();
void list_destroy(List *list);
int list_append(List *list, void *data);
void *list_get(List *list, size_t index);
void *list_dequeue(List *list);
void *list_head(List *list);
size_t list_size(List *list);

#endif // LIST_H