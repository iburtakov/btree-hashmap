#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "list.h"

const int DELTA = 10;

DLList* DLList_alloc()
{
    DLList* list = calloc(1, sizeof(DLList));

    return list;
}

int DLListInit(DLList* list, const char* name, int size)
{
    //assert(list);

    list->data = calloc(size, sizeof(data));

    list->dataMax = size;
    list->dataCur = 0;

    list->next = calloc(size, sizeof(int));

    for (int i = 1; i < size - 1; i++)
    {
        list->next[i] = i + 1;
    }
    list->next[size - 1] = 0;

    list->prev = calloc(size, sizeof(int));

    list->free = 1;
    list->head = 0;
    list->tail = 0;

    list->isSorted = 'y'; //sorted by phys adr

    return OK;
}

void DLListFree(DLList* list)
{
    if (list == NULL)
        return;

    if (list->data != NULL)
        free(list->data);

    if (list->next != NULL)
        free(list->next);

    if (list->prev != NULL)
        free(list->prev);

    free(list);
}

int DLListResize(DLList* list, const int sizeNew)
{
    if (sizeNew < 0)
    {
        //printf("invalid new size! %d -> %d\n", list->dataMax, sizeNew);
        return -1;
    }
    else if (sizeNew == list->dataMax)
    {
        //printf("same size %d -> %d\n", list->dataMax, sizeNew);
        return 0;
    }
    else if (sizeNew < list->dataMax)
    {
        //printf("shrink %d -> %d\n", list->dataMax, sizeNew);
        //DLListSort(list);

        list->dataCur = (list->dataCur > sizeNew) ? (sizeNew - DELTA) : (list->dataCur);
        list->dataMax = sizeNew;
        list->data = realloc(list->data, sizeNew * sizeof(data));
        list->next = realloc(list->next, sizeNew * sizeof(int));
        list->prev = realloc(list->prev, sizeNew * sizeof(int));
        list->tail = list->dataCur;
        list->next[list->tail] = 0;
    }
    else if (sizeNew > list->dataMax)
    {
        //printf("extend %d -> %d\n", list->dataMax, sizeNew);
        list->data = realloc(list->data, sizeNew * sizeof(data));
        list->next = realloc(list->next, sizeNew * sizeof(int));

        for (int i = list->dataMax; i < sizeNew - 1; i++)
        {
            list->next[i] = i + 1;
        }
        list->free = list->dataMax;
        list->next[sizeNew - 1] = 0;

        list->prev = realloc(list->prev, sizeNew * sizeof(int));
        memset(list->prev + list->dataMax * sizeof(int), '\0', (sizeNew - list->dataMax) * sizeof(int));
        list->dataMax = sizeNew;
    }
    return 0;
}

int DLListGetLen(DLList* list)
{
    return list->dataCur;
}

int DLListGetCap(DLList* list)
{
    return list->dataMax;
}

int DLListGetHead(DLList* list)
{
    return list->head;
}

int DLListGetTail(DLList* list)
{
    return list->tail;
}

int DLListGetPhysAddr(DLList* list, const int addrLogical)
{
    if (list->isSorted == 'y')
        return addrLogical;

    int addrPhysical = list->head;

    if (addrLogical >= list->dataMax)
    {
        //printf("no such address. too big\n");
        return -1;
    }
    else
    {
        for (int i = addrLogical; i > 0; i--)
            addrPhysical = list->next[addrPhysical];
    }

    return addrPhysical;
}

int DLListInsertL(DLList* list, const int addrPhysical, const data dat)
{
    if (list->dataCur >= list->dataMax - 1)
        DLListResize(list, list->dataMax * 2);

    if (list->prev[addrPhysical] == 0 && (addrPhysical != list->head && addrPhysical != list->tail))
    {
        //printf("unappropriate address to insert %d!\n", addrPhysical);
        return -1;
    }

    int addrIns = list->free;
    int addrNewFree = list->next[list->free];
    list->data[list->free] = dat;

    if (list->dataCur == 0)
    {
        list->prev[addrIns] = 0;
        list->next[addrIns] = 0;
        list->tail = addrIns;
        list->head = addrIns;
    }
    else if (addrPhysical == list->head)
    {
        list->prev[addrIns] = 0;
        list->next[addrIns] = list->head;
        list->prev[list->head] = addrIns;
        list->head = addrIns;
    }
    else if (addrPhysical != list->head)
    {
        list->prev[addrIns] = list->prev[addrPhysical];
        list->next[addrIns] = addrPhysical;
        list->next[list->prev[addrPhysical]] = addrIns;
        list->prev[addrPhysical] = addrIns;
    }

    list->dataCur++;
    list->isSorted = 'n';
    list->free = addrNewFree;

    return addrIns;
}

int DLListInsertR(DLList* list, const int addrPhysical, const data dat)
{
    if (list->dataCur >= list->dataMax - 1)
        DLListResize(list, list->dataMax * 2);

    if (list->prev[addrPhysical] == 0 && (addrPhysical != list->head || addrPhysical != list->tail)) {
        //printf("unappropriate address to insert %d!\n", addrPhysical);
        return -1;
    }

    int addrIns = list->free;
    int addrNewFree = list->next[addrIns];
    list->data[addrIns] = dat;

    if (list->dataCur == 0)
    {
        list->prev[addrIns] = 0;
        list->next[addrIns] = 0;
        list->tail = addrIns;
        list->head = addrIns;
    }
    else if (addrPhysical == list->tail)
    {
        list->next[addrIns] = 0;
        list->prev[addrIns] = list->tail;
        list->next[list->tail] = addrIns;
        list->tail = addrIns;
    }
    else if (addrPhysical != list->head)
    {
        list->next[addrIns] = list->next[addrPhysical];
        list->prev[addrIns] = addrPhysical;
        list->prev[list->next[addrPhysical]] = addrIns;
        list->next[addrPhysical] = addrIns;
        list->isSorted = 'n';
    }

    list->dataCur++;
    list->free = addrNewFree;

    return addrIns;
}

int DLListDelete(DLList* list, const int addrPhysical)
{
    if (list->dataCur == 0)
    {
        //printf("list is already empty!\n");
        return -1;
    }

    if (list->prev[addrPhysical] == 0 && (addrPhysical != list->head && addrPhysical != list->tail)) {
        //printf("unappropriate address to delete %d %d!\n", addrPhysical, list->head);
        return -1;
    }

    if (addrPhysical == list->head)
    {
        list->prev[list->next[addrPhysical]] = 0;
        list->head = list->next[addrPhysical];
        list->isSorted = 'n';
    }
    else if (addrPhysical == list->tail)
    {
        list->next[list->prev[addrPhysical]] = 0;
        list->tail = list->prev[addrPhysical];
    }
    else
    {
        list->prev[list->next[addrPhysical]] = list->prev[addrPhysical];
        list->next[list->prev[addrPhysical]] = list->next[addrPhysical];
        list->isSorted = 'n';
    }

    list->prev[addrPhysical] = 0;
    list->next[addrPhysical] = list->free;
    list->free = addrPhysical;
    list->dataCur--;

    if (list->dataCur <= list->dataMax / 2 - DELTA)
        DLListResize(list, list->dataMax / 2);

    return 0;
}

int DLListFind(DLList* list, const data dat)
{
    int addr = -1;
    /* for numeric data only
    for (int i = list->head; i != 0; i = list->next[i])
        if (list->data[i] == dat) {
            addr = i;
            break;
        }
    */
    return addr;
}

void DLListSort(DLList* list)
{

    if (list->isSorted == 'y' || list->dataCur < 1)
    {
        return;
    }

    data* dataSorted = calloc(list->dataMax, sizeof(data));

    int count = 1;
    for (int i = list->head; i != 0; i = list->next[i])
    {
        dataSorted[count] = list->data[i];
        count++;
    }

    free(list->data);
    list->data = dataSorted;

    for (int i = 1; i < list->dataMax - 1; i++)
        list->next[i] = i + 1;

    memset((char*)(list->prev), '\0', list->dataMax * sizeof(int));
    for (int i = 1; i <= list->dataCur; i++)
    {
        list->prev[i] = i - 1;
    }

    list->isSorted = 'y';
    list->head = 1;
    list->tail = list->dataCur;
    list->free = list->next[list->tail];
    list->next[list->tail] = 0;
    list->prev[list->head] = 0;
}