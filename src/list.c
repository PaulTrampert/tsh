#include "./list.h"
#include <stdlib.h>

ListNode *list_node_create(void *data);
void list_insert_before(ListNode *before, ListNode *new_node);
void list_insert_after(ListNode *after, ListNode *new_node);

void list_insert_before(ListNode *before, ListNode *new_node) {
    ListNode *after = before->prev;
    after->next = new_node;
    new_node->prev = after;
    new_node->next = before;
    before->prev = new_node;
}

void list_insert_after(ListNode *after, ListNode *new_node) {
    list_insert_before(after->next, new_node);
}

ListNode *list_node_create(void *data) {
    ListNode *node = malloc(sizeof(ListNode));
    if (!node) return NULL;

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

List *list_create() {
    List *list = malloc(sizeof(List));
    if (!list) return NULL;

    list->size = 0;
    list->head = list_node_create(NULL);
    if (!list->head) {
        free(list);
        return NULL;
    }
    list->tail = list_node_create(NULL);
    if (!list->tail) {
        free(list->head);
        free(list);
        return NULL;
    }

    list->head->next = list->tail;
    list->tail->prev = list->head;

    return list;
}

void list_destroy(List *list) {
    if (!list) return;

    ListNode *current = list->head;
    while (current) {
        ListNode *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int list_append(List *list, void *data) {
    if (!list) return -1;

    ListNode *new_node = list_node_create(data);
    if (!new_node) return -1;

    list_insert_before(list->tail, new_node);
    list->size++;

    return 0;
}

void *list_get(List *list, size_t index) {
    if (!list || index >= list->size) return NULL;

    ListNode *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    return current ? current->data : NULL;
}

size_t list_size(List *list) {
    return list ? list->size : 0;
}
