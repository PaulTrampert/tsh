
#include <stdlib.h>
#include "exit_codes.h"
#include "array_list.h"

#define INITIAL_CAPACITY 4
#define MAX_GROWTH 1024

struct _arrayList
{
    void **data;
    size_t size;
    size_t capacity;
};

ArrayList *array_list_create()
{
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
    if (!list)
        exit(EOOM);
    list->capacity = INITIAL_CAPACITY;
    list->size = 0;
    list->data = (void **)calloc(list->capacity + 1, sizeof(void *)); // +1 for NULL slot
    if (!list->data)
    {
        free(list);
        exit(EOOM);
    }
    return list;
}

void array_list_destroy(ArrayList *list, void (*item_destroyer)(void *))
{
    if (!list)
        return;
    if (item_destroyer)
    {
        for (size_t i = 0; i < list->size; i++)
        {
            item_destroyer(list->data[i]);
        }
    }
    free(list->data);
    free(list);
}

int array_list_append(ArrayList *list, void *item)
{
    if (!list)
        return 0;
    if (list->size == list->capacity)
    {
        size_t grow = list->capacity < MAX_GROWTH ? list->capacity : MAX_GROWTH;
        size_t new_capacity = list->capacity + grow;
        void **new_data = (void **)realloc(list->data, (new_capacity + 1) * sizeof(void *));
        if (!new_data)
            return 0;
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = item;
    list->data[list->size] = NULL; // maintain NULL slot
    return 1;
}

void *array_list_get(ArrayList *list, size_t index)
{
    if (!list || index >= list->size)
        return NULL;
    return list->data[index];
}

size_t array_list_size(ArrayList *list)
{
    if (!list)
        return 0;
    return list->size;
}

void **array_list_get_data(ArrayList *list)
{
    if (!list)
        return NULL;
    return list->data;
}
