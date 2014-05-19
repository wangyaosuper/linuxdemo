#ifndef WYCHDEV_H_
#define WYCHDEV_H_

typedef int (*MsgEvtProcessFunc)();
int memDev_init(unsigned int size , unsigned char **ppBuf, MsgEvtProcessFunc Process);
int memDev_exit();
int mem_wakeup_poll();


#endif
