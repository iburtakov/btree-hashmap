#pragma once

struct _Pair
{
    void* key;
    void* value;
};
typedef struct _Pair Pair;
typedef Pair data_t;

struct _Node
{
    struct _Node* next;
    data_t data;
};
typedef struct _Node Node;

struct _List
{
    Node* first;
    Node* last;

    int size;
};
typedef struct _List List;

// FUNCTIONS DECLARATION

List* ListAlloc();
int ListInit(List* lst);
int ListDelete(List* lst, Node* prev, Node* node);
int ListAppend(List* lst, data_t data);
void ListFree(List* lst);
void _ListFree(Node* node);