#include <dlfcn.h>
#include "demoloadershell.h"
#include "demoloaderlist.h"
#include "stdlib.h"


int showCase(DLList *pCaseList){
    DLListItem * pItem = dlGetBegin(pCaseList);
    CaseDescription *pCaseDes;
    unsigned int index = 0;
    printf("The list of Case:\n");
    for (;
         pItem != dlGetEnd(pCaseList);
         pItem = dlGetNext(pItem), ++index ){
        pCaseDes = (CaseDescription*)dlGetData(pItem);
        printf("%d. %s\n", 
               index,
               pCaseDes->pCaseName);               
    }
    printf("%d. Back to the up-level\n", index);
    printf("\n");

    return 0;
}

int showDemo(DLList *pDemoList){
    DLListItem * pItem = dlGetBegin(pDemoList);
    DemoDescription *pDemoDes;
    unsigned int index = 0;
    printf("The list of Demo:\n");
    for (;
         pItem != dlGetEnd(pDemoList);
         pItem = dlGetNext(pItem), ++index ){
        pDemoDes = (DemoDescription*)dlGetData(pItem);
        printf("%d. %s\n", 
               index,
               pDemoDes->pDemoName);               
    }
    printf("%d. Quit\n", index);
    printf("\n");

    return 0;
}


int getInput(char *pInputBuffer){
    printf("Please input the number you choice: ");
    scanf("%s", pInputBuffer);
    return 0;
}


#define LEN_OF_INPUT_BUFFER 100

int demoloadershell(DLList *pDemoList){
    int iRes;
    char inputBuffer[LEN_OF_INPUT_BUFFER];
    int iInputNum;
    DemoDescription * pChoicedDemoDes;
    CaseDescription * pChoicedCaseDes;
    DLListItem * pChoicedItem;
    void * pDlHandle = NULL;
    CaseFunc *pFun;
    while(1){
        iRes = showDemo(pDemoList);
        if (0 > iRes){
            printf("Show Demo List Error ! Program shutdown .");
            return iRes;
        }

        iRes = getInput(inputBuffer);
        if (0 > iRes){
            printf("get the key input failed ! Program shutdown .");
            return iRes;
        }

        iInputNum = atoi(inputBuffer);
        if (iInputNum < dlGetLen(pDemoList)){
            pChoicedDemoDes = (DemoDescription *)(dlGetData((dlGetByNum(pDemoList, iInputNum))));
            if (NULL == pChoicedDemoDes){
                /*todo*/
                continue;
            }
            if (NULL != pDlHandle){
                dlclose(pDlHandle);
            }
            pDlHandle = dlopen(pChoicedDemoDes->pSoName, RTLD_LAZY);
            if (NULL == pDlHandle){
                printf("Error : The so[%s] of this demo can't be load, please choice other's demo.",
                       pChoicedDemoDes->pSoName);
                continue;
            }
        }
        else if (iInputNum == dlGetLen(pDemoList)){
            break;            
        }
        else {
            continue;
        }
        while (1){
            iRes = showCase(pChoicedDemoDes->pCaseList);
            if (0 > iRes){
                printf("Show Case List Error ! Program shutdown .");
                return iRes;
            }

            iRes = getInput(inputBuffer);
            if (0 > iRes){
                printf("get the key input failed ! Program shutdown .");
                return iRes;
            }
            
            iInputNum = atoi(inputBuffer);
            if (iInputNum < dlGetLen(pChoicedDemoDes->pCaseList)){
                pChoicedItem  = dlGetByNum(pChoicedDemoDes->pCaseList, iInputNum);
                pChoicedCaseDes = (CaseDescription *)(dlGetData(pChoicedItem));
                if (NULL == pChoicedDemoDes){
                    printf("get the case description failed , please choice another case.");
                    continue;
                }
                pFun = dlsym(pDlHandle, pChoicedCaseDes->pCaseFunc);
                if (NULL == pFun){
                    printf("Get the function[%s] of the case failed, please choice another case.",
                           pChoicedCaseDes->pCaseFunc);
                    continue;
                }
            }
            else if (iInputNum == dlGetLen(pChoicedDemoDes->pCaseList)){
                break;            
            }
            else {
                continue;
            }
            
            pFun(NULL);
        }

    }

    return 0;
}

