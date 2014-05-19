#include "demodescription.h"
#include <expat.h>
#include <sys/stat.h>
#include <fcntl.h>

enum EN_STAT_OF_XML_PARSE{
    EN_STAT_OF_XML_PARSE_DEFAULT,
    EN_STAT_OF_XML_PARSE_TEST
};

typedef struct TTmpXmlParseData{
    int iDepth;
    enum EN_STAT_OF_XML_PARSE eState;
    DLList *pList;
}TmpXmlParseData;


static void XMLCALL
dataHandle(void *data, const XML_Char *s, int len)
{
    DemoDescription *pDemo;
    CaseDescription *pCase;
    char *pSrcFileNameBuf;
    DLListItem* pItem;
    if (EN_STAT_OF_XML_PARSE_TEST != 
        ((TmpXmlParseData*)data)->eState){
        return;
    }
    pItem = 
        dlGetTail(((TmpXmlParseData*)data)->pList);
    if (NULL == pDemo){
        printf("get the tail demo failed when parse the demo xml!");
        exit(-1);
    }
    pDemo = dlGetData(pItem);
    pItem = dlGetTail(pDemo->pCaseList);
    if (NULL == pItem){
        printf("get the tail case failed when parse the demo xml!");
        exit(-1);
    }
    pCase = dlGetData(pItem);
    pSrcFileNameBuf = 
        malloc(len + 1);
    if (NULL == pSrcFileNameBuf){
        printf("malloc the Src File Name Buffer failed when parse the demo xml!");
        exit(-1);
    }
    memcpy(pSrcFileNameBuf, s, len);
    pSrcFileNameBuf[len] = 0;
    pItem = 
        dlInsertItemToListTail(pCase->pSrcFileList, pSrcFileNameBuf);
    if (NULL == pItem){
        printf("insert the item to the Src File List Tail failed when parse the demo xml!");
        exit(-1);
    }
}

static void XMLCALL
start(void *data, const char *el, const char **attr)
{
    int i;
    int iRes;
    if(0 == strcmp("Demo", el)){
        DemoDescription *pDes = malloc(sizeof(DemoDescription));
        if (NULL == pDes){
            printf("malloc memory failed when parse the demo xml!");
            exit(-1);
        }
        for(i = 0; attr[i]; i+=2){
            if (0 == strcmp(attr[i], "Name")){
                pDes->pDemoName = malloc(strlen(attr[1+i]) + 1);
                if(NULL == pDes->pDemoName){
                    printf("malloc memory failed when parse the demo xml!");
                    exit(-1);
                }
                strcpy(pDes->pDemoName, attr[i + 1]);
            }
            else if(0 == strcmp(attr[i], "Library")){
                pDes->pSoName = malloc(strlen(attr[1+i]) + 1);
                if(NULL == pDes->pDemoName){
                    printf("malloc memory failed when parse the demo xml!");
                    exit(-1);
                }
                strcpy(pDes->pSoName, attr[i + 1]);
            }
        }
        pDes->pCaseList = dlCreateList();
        if (NULL == pDes->pCaseList){
            printf("create case list failed when parse the demo xml!");
            exit(-1);
        }
        DLListItem *res = 
            dlInsertItemToListTail(((TmpXmlParseData*)data)->pList, pDes);
        if (NULL == res){
            printf("list operato failed when parse the demo xml!");
            exit(-1);
        }
    }
    else if (0 == strcmp("Case", el)){
        DLListItem *pItem = 
            dlGetTail(((TmpXmlParseData*)data)->pList);
        if (NULL == pItem){
            printf("get the list tail failed when parse the demo xml!");
            exit(-1);
        }
        DemoDescription *pDes = dlGetData(pItem);
        if (NULL == pDes){
            /*to do*/ 
            /*This protected code is no need.*/
            printf("get the list tail Null when parse the demo xml!");
            exit(-1);
        }
        CaseDescription *pCase = 
            malloc(sizeof(CaseDescription));
        if (NULL == pCase){
            printf("malloc Case Description failed when parse the demo xml.");
            exit(-1);
        }

        for(i = 0; attr[i]; i+=2){
            if (0 == strcmp(attr[i], "Name")){
                pCase->pCaseName = malloc(strlen(attr[1+i]) + 1);
                if(NULL == pDes->pDemoName){
                    printf("malloc memory failed when parse the demo xml!");
                    exit(-1);
                }
                strcpy(pCase->pCaseName, attr[i + 1]);
            }
            else if(0 == strcmp(attr[i], "CaseFunc")){
                pCase->pCaseFunc = malloc(strlen(attr[1+i]) + 1);
                if(NULL == pCase->pCaseFunc){
                    printf("malloc memory failed when parse the demo xml!");
                    exit(-1);
                }
                strcpy(pCase->pCaseFunc, attr[i + 1]);
            }
        }
        
        pCase->pSrcFileList = 
            dlCreateList();
        if (NULL == pCase->pSrcFileList){
            printf("create src file list failed when parse the demo xml!");
            exit(-1);
        }
        
        
        /*add the case to demo*/
        DLListItem *pRes = 
            dlInsertItemToListTail(pDes->pCaseList, pCase);
        if (NULL == pRes){
            printf("insert item to case list tail failed when parse the demo xml!");
            exit(-1);
        }
    }
    else if (0 == strcmp("Text", el)){
        ((TmpXmlParseData*)data)->eState = 
            EN_STAT_OF_XML_PARSE_TEST;
    }
}

static void XMLCALL
end(void *data, const char *el)
{
    --(((TmpXmlParseData*)data)->iDepth);
    if (0 == strcmp("Text", el)){
        ((TmpXmlParseData*)data)->eState = 
            EN_STAT_OF_XML_PARSE_DEFAULT;
    }
}

/*
typedef struct TFileStat{
    mode_t st_mode;
    ino_t st_ino;
    dev_t st_dev;
    dev_t st_rdev;
    nlink_t st_nlink;
    uid_t st_uid;
    gid_t st_gid;
    off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
    blksize_t st_blksize;
    blkcnt_t st_blocks;
}FileStat;
*/
typedef struct TFileStat {
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */
    uid_t     st_uid;     /* user ID of owner */
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file) */
    off_t     st_size;    /* total size, in bytes */
    char     protect[1000];
}FileStat;

static int 
loadXmlFileAndCreateBuffer(const char * pFileName,
                           char ** ppBuffer, 
                           size_t *pLen){
    int iRes;
    FileStat fs;
    char * pPos;
    size_t leftSize;
    int file;
    if (NULL == ppBuffer || NULL == pLen){
        goto parameterWrong;
    }
    iRes = stat(pFileName, &fs);
    if (0 != iRes){
        goto getFileStatWrong;
    }
    leftSize = fs.st_size + 6000;
    *ppBuffer = (char *)malloc(leftSize);
    if (NULL == ppBuffer){
        goto mallocBufferFailed;
    }
    pPos = *ppBuffer;

    file = open(pFileName, O_RDONLY);
    if (file < 0){
        goto openFile;
    }
    
    *pLen = 0;
    do{
        iRes = read(file,
                    pPos,
                    leftSize);
        leftSize -= iRes;
        pPos += iRes;
        if (iRes > 0){
            *pLen += iRes;
        }
        else{
            break;
        }
    }while(1);
    close(file);        

    return 0;
 openFile:
    /*todo*/
    free(*ppBuffer);
    *ppBuffer = NULL;

 mallocBufferFailed:
    /*todo*/
 getFileStatWrong:
    /*todo*/    
 parameterWrong:
    /*todo*/
    return -1;
    
}


static int 
unloadXmlFileAndDestroyBuffer(char ** ppBuffer){
    free(*ppBuffer);
    *ppBuffer = NULL;
    return 0;
}

DemoDescription *  loadDemoDescription(){
    TmpXmlParseData *pTmpData;
    int done;
    char *pBuff;
    int len;
    int iRes;
    DLList *pRetList;
    pTmpData = 
        malloc(sizeof(TmpXmlParseData));
    if(NULL == pTmpData){
        goto mallocXmlParseDataFailed;
    }
               
    pTmpData->pList = dlCreateList();
    pTmpData->iDepth = 0;
    pTmpData->eState = EN_STAT_OF_XML_PARSE_DEFAULT;
    pTmpData->pList = dlCreateList();
    if (NULL == pTmpData->pList){
        goto createListFailed;
    }
    
    iRes = loadXmlFileAndCreateBuffer("./democase.xml",
                               &pBuff,
                               &len);
    if (iRes < 0){
        goto loadXmlFailed;
    }

    XML_Parser p = XML_ParserCreate(NULL);
    if (! p) {
        goto createParserFailed;
    }

    XML_SetUserData(p, pTmpData);
    XML_SetCharacterDataHandler(p, dataHandle);
    XML_SetElementHandler(p, start, end);

    
    if (XML_Parse(p, pBuff, len, done) == XML_STATUS_ERROR) {
        goto parserXmlFailed;      
    }

    
    XML_ParserFree(p);
    unloadXmlFileAndDestroyBuffer(&pBuff);

    pRetList = pTmpData->pList;
    free(pTmpData);
    pTmpData = NULL;
    return pRetList;

 parserXmlFailed:
    printf("Parse error at line %u:\n%s\n",
           XML_GetCurrentLineNumber(p),
           XML_ErrorString(XML_GetErrorCode(p)));
    XML_ParserFree(p);

 createParserFailed:
    unloadXmlFileAndDestroyBuffer(&pBuff);
 loadXmlFailed:
    /*todo*/
    dlDestroyList(&pTmpData->pList);

    
 createListFailed:
    /*todo*/
    free(pTmpData);
    pTmpData = NULL;
 mallocXmlParseDataFailed:
    /*todo*/
    return NULL;
}

int unLoadDemoDescription(DemoDescription ** ppDes){
    if(NULL == ppDes){
        return -1;
    }
    free(*ppDes);
    *ppDes = NULL;
    return 0;
}

