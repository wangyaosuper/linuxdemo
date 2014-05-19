#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "wychdev.h"
int  wydev_init(void)
{
    int iRes;
    printk(KERN_INFO "[wydev]wydev init.\n");
    iRes = chdev_init();
    return 0;
}

module_init(wydev_init);

void wydev_exit(void)
{
    int iRes;
    iRes = chdev_exit();
    printk(KERN_INFO "[wydev]wydev exit.\n");
}
module_exit(wydev_exit);


