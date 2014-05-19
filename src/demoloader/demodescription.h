#ifndef _DEMODESCRIPTION_H_
#define _DEMODESCRIPTION_H_


#include "demoloaderlist.h"
typedef struct TDemoDescription{
    char * pDemoName;
    char * pSoName;
    DLList * pCaseList;
}DemoDescription;

typedef int (CaseFunc)(void *);

typedef struct TCaseDescription{
    char * pCaseName;
    char * pCaseFunc;
    DLList * pSrcFileList;
}CaseDescription;


#endif

