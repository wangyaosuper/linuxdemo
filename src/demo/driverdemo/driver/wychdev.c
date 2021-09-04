#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include "wychdev.h"

#define DEV_ID_COUNT 10

dev_t g_wy_ch_dev;
struct cdev * g_pdev;


static int char_read(struct file *filp,char __user *buffer,size_t,loff_t *);
static int char_open(struct inode *,struct file *);
static int char_write(struct file *filp,const char __user *buffer,size_t ,loff_t*);
static int char_release(struct inode *,struct file *); 

struct file_operations Fops = {
    .read = char_read,
    .write = char_write,
    .open = char_open,
    .release = char_release,/* a.k.a. close */
};


int chdev_init(void){
    int iRes, devno;
    
    iRes = alloc_chrdev_region(&g_wy_ch_dev,0,DEV_ID_COUNT,"wychdev");
    if (likely(0 == iRes)){
        printk(KERN_INFO "[wychdev] alloc_chrdev_region succeful, Major=%d, minor=%d.\n",
               MAJOR(g_wy_ch_dev),
               MINOR(g_wy_ch_dev));
    }
    else{
        printk(KERN_INFO "[wychdev] alloc_chrdev_region fail, iRes=%d.\n",
               iRes);
        return -1;
    }

    g_pdev = cdev_alloc();
    cdev_init(g_pdev, &Fops);
    iRes = cdev_add(g_pdev, g_wy_ch_dev, 1);
    if (likely(0 == iRes)){
        printk(KERN_INFO "[wychdev] cdev_add succeful.\n");
    }
    else{
        printk(KERN_INFO "[wychdev] cdev_add fail, iRes-%d.\n", iRes);
        return -2;
    }

    return 0;
}


int chdev_exit(void){
    cdev_del(g_pdev);
    printk(KERN_INFO "[wychdev] cdev_del successful.\n");
    unregister_chrdev_region(g_wy_ch_dev,DEV_ID_COUNT);
    printk(KERN_INFO "[wychdev] unregister_chrdev_region successful.\n");
    return 0;
}


int char_read(struct file *filp,char __user *buffer,size_t size, loff_t * offp){
    printk(KERN_INFO "[wychdev] enter char_read().\n");
    char str[] = "hi this is char driver demo.";
    copy_to_user(buffer, str, sizeof(str));
    *offp = sizeof(str);
    return sizeof(str);
}

int char_open(struct inode * nodep,struct file * filep){
    return 0;
}

int char_write(struct file *filep,const char __user *buffer,size_t size,loff_t * offp){
    return 0;
}

int char_release(struct inode * nodep,struct file * filep){
    return 0;
}

