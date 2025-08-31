#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stddef.h>

typedef struct _arrayList ArrayList;

ArrayList *array_list_create();
void array_list_destroy(ArrayList *list);
int array_list_append(ArrayList *list, void *item);
void *array_list_get(ArrayList *list, size_t index);
size_t array_list_size(ArrayList *list);

#endif // ARRAY_LIST_H