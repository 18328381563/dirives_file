// include head files
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mman.h>
#include <linux/random.h>
#include <linux/init.h>
#include <linux/raw.h>
#include <linux/tty.h>
#include <linux/capability.h>
#include <linux/ptrace.h>
#include <linux/device.h>
#include <linux/highmem.h>
#include <linux/backing-dev.h>
#include <linux/shmem_fs.h>
#include <linux/splice.h>
#include <linux/pfn.h>
#include <linux/export.h>
#include <linux/io.h>
#include <linux/uio.h>
#include <linux/module.h>
#include <linux/uaccess.h>


// 1确定主设备号，也可以让内核分配
static int major = 0;

// 实现函数
static int hello_open(struct inode *inode, struct file *filp)
{
    printk("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
    return 0;
}
static ssize_t hello_read (struct file *filp, char __user *buf, size_t size, loff_t *offset)
{
    printk("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
    return size;
}
static ssize_t hello_write (struct file * flip, const char __user *buf, size_t size, loff_t *offset)
{
    printk("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
    return size;
}
static int hello_release (struct inode *node, struct file *flip)
{
    printk("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
    return 0;
}
//2.定义自己的 file_operations结构体

static const struct file_operations hello_dev = {
    .owner = THIS_MODULE,
	.read = hello_read,
    .write = hello_write,
    .open =  hello_open,
    .release = hello_release
};



//
static int hello_dev_init(void)
{

	major=register_chrdev(0, "hello", &hello_dev);
    return 0;

}
static void hello_dev_exit(void)
{
    unregister_chrdev(major, "hello");
}

// 指定协议 指定出口，指定入口
module_init(hello_dev_init);
module_exit(hello_dev_exit);
MODULE_LICENSE("GPL");