#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

List* ListAlloc()
{
    List* lst = calloc(1, sizeof(List));

    if (lst == NULL)
        return NULL;
    else
        return lst;
}

int ListInit(List* lst)
{
    if (lst == NULL)
        return -1;

    lst->first = NULL;
    lst->last = NULL;
    lst->size = 0;

    return 0;
}

int ListDelete(List* lst, Node* prev, Node* node)
{
    assert(lst);

    if (lst->size == 0 || (prev == NULL && node == NULL))
        return -1;
    else if (prev != NULL && node != NULL)
    {
        if (prev->next == lst->last)
            lst->last = prev;

        Node* tmp = prev->next;
        prev->next = (prev->next)->next;
        free(tmp);
    }
    else if (prev == NULL && node != NULL)
    {
        Node* node = lst->first;

        lst->first = (lst->first)->next;
        free(node);
    }

    lst->size--;

    return 0;
}

int ListAppend(List* lst, data_t data)
{
    assert(lst);

    Node* node = calloc(1, sizeof(Node));

    if (node != NULL) {
        if (lst->size != 0)
            (lst->last)->next = node;
        else
            lst->first = node;

        node->next = NULL;
        node->data = data;

        lst->last = node;
        lst->size++;
    }
    else
    {
        return -1;
    }

    return 0;
}

void ListFree(List* lst)
{
    if (lst == NULL)
        return;

    _ListFree(lst->first);
}

void _ListFree(Node* node)
{
    if (node == NULL)
        return;

    _ListFree(node->next);

    free(node);
}