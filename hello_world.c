#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static u8 idx = 0;
static u8 ch_val = 0x00;
//static charp my_str = NULL;

static int idx_set(const char *val, const struct kernel_param *kp)
{
    int ret = 0;
    u8 tmp = 0;
    ret = kstrtou8(val, 10, &tmp);
    if (ret) {
        pr_err("kst_error!\n");
    } else {
	if (tmp>13) {
	    pr_err("value for idx must be from 0 to 13! you try to set %d\n", tmp);
	} else {
	    idx = tmp;
            pr_info("idx value = %d\n", idx);
	}
    }
    return ret;
}

static int idx_get(char *val, const struct kernel_param *kp)
{
    return sprintf(val, "%d\n", idx);
}

static const struct kernel_param_ops idx_ops =
{
    .set = idx_set,
    .get = idx_get
};


module_param_cb(idx, &idx_ops, &idx, 0644);
//module_param_cb(ch_val, &ch_val_ops, &ch_val, 0644);
//module_param_cb(my_str, &my_str_ops, &my_str, 0444);


MODULE_PARM_DESC(idx, "Индекс в массиве");
//MODULE_PARM_DESC(ch_val, "Символ ASCII");
//MODULE_PARM_DESC(my_str, "Строка-результат");

static int __init hello_init(void)
{
	pr_info("init\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Sivokhin");
MODULE_DESCRIPTION("HW_02_hello_world");
MODULE_VERSION("0.0.1");
