#ifndef _MSG_DEV_H_
#define _MSG_DEV_H_
#include <linux/mm.h> 

typedef int (*EvtNotify)();

unsigned char * msgDevInit(unsigned char *pMsgPool, EvtNotify evt_notify);

int msg_mem_mmap(struct file *filp, struct vm_area_struct *vma, unsigned char *mem_msg_buf);

int msg_Evt_Process();

unsigned int msg_get_msg_pool_memory_size();

int msg_send_msg(unsigned char *pData, unsigned int len);


#endif
