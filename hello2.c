#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"


MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello1 module");
MODULE_AUTHOR("Fedoniuk Roman IO-24");

static uint hello_world_times = 1;
module_param(hello_world_times, uint, 0644);
MODULE_PARM_DESC(hello_world_times, "Number of times you want to print 'Hello, world!'");

static int __init hello2_init(void)
{
	pr_info("Calling print_hello() from Hello1 module\n");
	print_hello(hello_world_times);
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Module Hello2 done\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
