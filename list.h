#pragma once
#include "map.h"
#define DLLIST_INIT(list, size) DLListInit(list, #list, size)

//structure of atomic element in list structure
struct _Pair
{
    void* key;
    void* value;
};

typedef struct _Pair Pair;
typedef Pair data;

enum DLListErrs {
    OK,
    E_INIT_ERR,
    E_REALLOC_ERR,
    E_LIST_OVERWLOW,
    E_LIST_UNDERFLOW,
    E_CORRUPTED_SEQ,
    E_INV_SIZE,
};

//--------------------------------------------------------------------------------

//Main data type in this data structure
struct _DLList
{
    data* data;         // data array
    int dataMax;        // data array capacity
    int dataCur;        // data array current load

    int* next;          // sequence of physical addresses, indicates next element
    int* prev;          // sequence of physical addresses, indicates previous element

    int free;           // physical address of first free element
    int head;           // physical address of first element
    int tail;           // physical address of last element

    char isSorted;      // y/n sorted by phys adr
};

typedef struct _DLList DLList;

//--------------------------------------------------------------------------------
/**
 * @brief this function allocates memory for pointer to the DLList structure.
 *
 * @return DLList* list - pointer to the allocated memory.
 */
DLList* DLListAlloc();

/**
 * @brief this function initializes DLList structure pointed by list.
 * @note better use DLLIST_INIT(list) macro, it automatically assigns list's name.
 *
 * @param DLList* list     - pointer to the structure;
 * @param const char* name - name for the future structure;
 * @param int size         - initial size of the list.
 *
 * @return int res         - 0 if initialised successfully, non-zero else.
 */
int DLListInit(DLList* list, const char* name, int size);

/**
* @brief this function deallocates all of the memory, assigned to the list.
*
* @param DLList* list - pointer to the structure.
*/
void DLListFree(DLList* list);

/**
 * @brief this function sets list's size to sizeNew and sort it by phys adr of any data in it.
 * @note not intended for user usage.
 *
 * @param DLList* list      - pointer to the structure;
 * @param const int sizeNew - new size of the list.
 *
 * @return int res          - 0 if success, non-zero otherwise.
 */
int DLListResize(DLList* list, const int sizeNew);

///need GetHash???

/**
 * @brief this fuction gets list's current load.
 *
 * @param DLList* list - pointer to the structure.
 *
 * @return int len     - list's length.
 */

int DLListGetLen(DLList* list);

/**
 * @brief this fuction gets list's current capacity.
 *
 * @param DLList* list - pointer to the structure.
 *
 * @return int cap     - list's capacity.
 */

/**
 * @brief this fuction gets list's current capacity.
 *
 * @param DLList* list - pointer to the structure.
 *
 * @return int cap     - list's capacity.
 */
int DLListGetCap(DLList* list);

/**
 * @brief this fuction gets list's current physical address of the head.
 *
 * @param DLList* list - pointer to the structure.
 *
 * @return int head    - list's head.
 */
int DLListGetHead(DLList* list);

/**
 * @brief this fuction gets list's current physical address of the tail.
 *
 * @param DLList* list - pointer to the structure.
 *
 * @return int tail    - list's tail.
 */
int DLListGetTail(DLList* list);

/**
 * @brief this fuction gets element's physical address.
 *
 * @param DLList* list          - pointer to the structure;
 * @param const int addrLogical - element's logical number.
 *
 * @return int addr             - element's physical address.
 */
int DLListGetPhysAddr(DLList* list, const int addrLogical);

/**
 * @brief this function inserts element with given value left-side of the element with given physical address.
 *
 * @param DLList* list           - pointer to the structure;
 * @param const int addrPhysical - physical address of the element;
 * @param const data dat         - value of the new element.
 *
 * @return int addr              - physical address of the new element.
 */
int DLListInsertL(DLList* list, const int addrPhysical, const data dat);

/**
 * @brief this function inserts element with given value right-side of the element with given physical address.
 *
 * @param DLList* list           - pointer to the structure;
 * @param const int addrPhysical - physical address of the element;
 * @param const data dat         - value of the new element.
 *
 * @return int addr              - physical address of the new element.
 */
int DLListInsertR(DLList* list, const int addrPhysical, const data dat);

/**
 * @brief this function deletes element with given physical address.
 *
 * @param DLList* list           - pointer to the structure;
 * @param const int addrPhysical - physical address of the element.
 *
 * @return int res               - 0 if deleted successfully, non-zero otherwise.
 */
int DLListDelete(DLList* list, const int addrPhysical);

/**
 * @brief this function searches for first instance of element with given value.
 *
 * @param DLList* list   - pointer to the structure;
 * @param const data dat - value to search for.
 *
 * @return addr          - physical address of the firsh instance. -1 if not found.
 */
int DLListFind(DLList* list, const data dat);

/**
 * @brief this function sorts given list, so that physical number of each element would correspond to the logical one of it.
 *
 * @param DLList* list - pointer to the structure.
 */
void DLListSort(DLList* list);