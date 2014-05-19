#ifndef _DEMOLOADERLIST_H_
#define _DEMOLOADERLIST_H_

typedef struct TDLListItem{
    struct DLListItem * pPre;
    struct DLListItem * pNext;
    void * pData;
} DLList;
typedef struct TDLListItem DLListItem;


DLList* dlCreateList();
int dlDestroyList(DLList**);
DLListItem* dlGetBegin(DLList*);
DLListItem* dlGetTail(DLList*);
DLListItem* dlGetEnd(DLList*);
DLListItem* dlGetNext(DLListItem*);
DLListItem* dlGetByNum(DLList* , unsigned int );
void* dlGetData(DLListItem*);
DLListItem* dlInsertItemToListHead(DLList* pList, void *);
DLListItem* dlInsertItemToListTail(DLList* pList, void *);
void * dlDelItem(DLListItem**);
unsigned int dlGetLen(DLList*);

#endif
