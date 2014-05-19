#include <stdio.h>
#include "demoloaderxml.h"
#include "demoloadershell.h"

const char g_demoloader_version[] = "demoloader_V1.1";

int main(){
    DLList *pDemoDesList;
    int iRes;
    printf("start linux demo loader, version = %s\n",
           g_demoloader_version);
    pDemoDesList = loadDemoDescription();
    if(NULL == pDemoDesList){
        goto loadDemoDescriptionFailed;
    }
    iRes = demoloadershell(pDemoDesList);
    
    unLoadDemoDescription(pDemoDesList);
    
    printf("stop linux demo loader\n");
    return 0;
 loadDemoDescriptionFailed:
    /*todo*/
    return -1;
}
