#include "demoloaderlist.h"
#include <malloc.h>


DLList* 
dlCreateList(){
    DLList* pTemp =
        (DLList*)(malloc(sizeof(DLList)));
    if (NULL == pTemp){
        /*todo*/
        return NULL;
    }
    pTemp->pNext = (struct DDListItem*)pTemp;
    pTemp->pPre = (struct DDListItem*)pTemp;
    pTemp->pData = NULL;
    return pTemp;
}

int
dlDestroyList(DLList **ppList){
    DLListItem *pTemp, *pNext;
    if (NULL == ppList){
        /*todo*/
        return -1;
    }
    pTemp = dlGetBegin(*ppList);
    while(dlGetEnd(*ppList) != pTemp){
        pNext = pTemp->pNext;
        free(pTemp);
        pTemp = pNext;
    }
    free(*ppList);
    *ppList = NULL;
    return 0;
}

DLListItem* 
dlGetBegin(DLList* pList){
    if (NULL == pList){
        /*todo*/
        return NULL;
    }
    if (pList->pNext == pList){
        return NULL;
    }
    return pList->pNext;
}

DLListItem* 
dlGetEnd(DLList* pList){
    if (NULL == pList){
        /*todo*/
        return NULL;
    }
    return pList;
}

DLListItem* 
dlGetTail(DLList* pList){
    if (NULL == pList){
        /*todo*/
        return NULL;
    }
    if (pList->pPre == pList){
        return NULL;
    }
    return pList->pPre;
}


DLListItem* 
dlGetPre(DLListItem* pItem){
    if (NULL == pItem){
        /*todo*/
        return NULL;
    }
    return pItem->pPre;
}


DLListItem* 
dlGetNext(DLListItem* pItem){
    return pItem->pNext;
}

DLListItem* 
dlGetByNum(DLList* pList, unsigned int iNum){
    DLListItem * pItem;
    unsigned int index = 0;
    if (NULL == pList){
        /*todo*/
        return NULL;
    }
    for (pItem = dlGetBegin(pList);
         pItem != dlGetEnd(pList); 
         ++index,  pItem = dlGetNext(pItem)){
        if (iNum == index){
            return pItem;
        }
    }
    return NULL;
}


void* 
dlGetData(DLListItem* pItem){
    if (NULL == pItem){
        /*todo*/
        return NULL;
    }
    return pItem->pData;
}


DLListItem* 
dlInsertItemToListHead(DLList* pList, void *pData){
    DLListItem* pTemp, *pNext;
    if (NULL == pList){
        /*todo*/
        return NULL;
    }    
    pTemp =
        (DLList*)(malloc(sizeof(DLList)));
    if (NULL == pTemp){
        /*todo*/
        return NULL;
    }
    pTemp->pData = pData;
    pNext = pList->pNext;
    pList->pNext = pTemp;
    pTemp->pNext = pNext;
    pNext->pPre = pTemp;
    pTemp->pPre = pList;
    return pTemp;    
}

DLListItem* 
dlInsertItemToListTail(DLList* pList, void * pData){
    DLListItem* pTemp, * pPre;
    if (NULL == pList){
        /*todo*/
        return NULL;
    }    
    pTemp =
        (DLList*)(malloc(sizeof(DLList)));
    if (NULL == pTemp){
        /*todo*/
        return NULL;
    }
    pTemp->pData = pData;
    pPre = pList->pPre;
    pList->pPre = pTemp;
    pTemp->pPre = pPre;
    pPre->pNext = pTemp;
    pTemp->pNext = pList;
    return pTemp;    
}

void * 
dlDelItem(DLListItem** ppItem){
    void *pData ;
    if (NULL == ppItem){
        /*todo*/
        return NULL;
    }
    pData = (*ppItem)->pData;
    free(*ppItem);
    (*ppItem) = NULL;
    return pData;
}

unsigned int dlGetLen(DLList* pList){
    DLListItem * pItem;
    unsigned int index = 0;
    if (NULL == pList){
        /*todo*/
        return NULL;
    }
    for (pItem = dlGetBegin(pList);
         pItem != dlGetEnd(pList); 
         ++index,  pItem = dlGetNext(pItem)){}
    return index;
}
