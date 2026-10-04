#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void)
{
	pr_info("%s:init\n", KBUILD_MODNAME);
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("%s:exit\n", KBUILD_MODNAME);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Sivokhin");
MODULE_DESCRIPTION("HW_02_hello_world");
MODULE_VERSION("0.0.1");
