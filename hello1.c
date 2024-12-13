#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello1 module");
MODULE_AUTHOR("Fedoniuk Roman IO-24");

static LIST_HEAD(hello_list);



void print_hello(int hello_world_times)
{
	struct hello_world_entry *entry;
	int i;

	BUG_ON(hello_world_times <= 0 || hello_world_times > 10);
	if (hello_world_times == 0 || hello_world_times > 10) {
		pr_err("Error, hello_world_times out of bounds 0 to 10: %d\n", hello_world_times);
		return;
	}

	if (hello_world_times == 0 || (hello_world_times >= 5 && hello_world_times <= 10)) {
		pr_warn("Warning, hello_world_times=%d: The number is 0 or in range(5, 10)\n", hello_world_times);
	}

	for (i = 0; i < hello_world_times; i++) {
		if (i == 4) {
			pr_err("Simulated error: kmalloc() returned NULL for the 5th element\n");
			continue;
		}
		entry = kmalloc(sizeof(*entry), GFP_KERNEL);
		if (!entry) {
			pr_err("Error, cannot allocate memory\n");
			return;
		}

		entry->start_time = ktime_get();
		pr_info("Hello, world!\n");
		entry->end_time = ktime_get();
		list_add_tail(&entry->list, &hello_list);
	}
}

EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct hello_world_entry *entry, *tmp;
	list_for_each_entry_safe(entry, tmp, &hello_list, list) {
	pr_info("Took time: %lld ns\n",
		ktime_to_ns(entry->end_time) - ktime_to_ns(entry->start_time));
	list_del(&entry->list);
	kfree(entry);
	}
}

module_exit(hello1_exit);
