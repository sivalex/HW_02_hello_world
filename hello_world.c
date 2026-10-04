#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

// valid value range: from 0 to 13
static u8 idx = 0xff;
static bool idx_changed = false;

// valid value range: from 0x20 to 0x7e
static u8 ch_val = 0x0;
static bool ch_val_changed = false;

// output, read only
#define MY_STR_SIZE 13
static char my_str[MY_STR_SIZE];


static void try_update_my_str(void)
{
    if (idx_changed && ch_val_changed) {
	my_str[idx] = ch_val;
	idx_changed = false;
	ch_val_changed = false;
    }
}

static int idx_set(const char *val, const struct kernel_param *kp)
{
    int ret = 0;
    u8 tmp = 0;
    ret = kstrtou8(val, 10, &tmp);
    if (ret) {
        pr_err("kst_error!\n");
    } else {
	if (tmp>12) {
	    pr_err("value for idx must be from 0 to 12! you try to set %d\n", tmp);
	} else {
	    idx = tmp;
            pr_info("set idx value to %d\n", idx);
	    idx_changed = true;
	    try_update_my_str();
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

static int ch_val_set(const char *val, const struct kernel_param *kp)
{
    int ret = 0;
    u8 tmp = 0;
    ret = kstrtou8(val, 16, &tmp);
    if (ret) {
        pr_err("kst_error!\n");
    } else {
	if (tmp<0x20 || tmp>0x7e) {
	    pr_err("value for ch_val must be from 0x20 to 0x7e! you try to set 0x%02x\n", tmp);
	    ret = EINVAL;
	} else {
	    ch_val = tmp;
            pr_info("set ch_val value to char: %c, hex: 0x%02x\n", ch_val, ch_val);
	    ch_val_changed = true;
	    try_update_my_str();
	}
    }
    return ret;
}

static int ch_val_get(char *val, const struct kernel_param *kp)
{
    //return sprintf(val, "Char: %c, Hex: 0x%02x\n", ch_val, ch_val);
    return sprintf(val, "%c\n", ch_val);
}

static const struct kernel_param_ops ch_val_ops =
{
    .set = ch_val_set,
    .get = ch_val_get
};

static int my_str_get(char *val, const struct kernel_param *kp)
{
    pr_info("my_str_get");
    //return scnprintf(val, MY_STR_SIZE+1, "%s\n", my_str);
    return sprintf(val, "%s\n", my_str);
}

static const struct kernel_param_ops my_str_ops =
{
    .get = my_str_get
};

module_param_cb(idx, &idx_ops, &idx, 0644);
module_param_cb(ch_val, &ch_val_ops, &ch_val, 0644);
module_param_cb(my_str, &my_str_ops, &my_str, 0444);

MODULE_PARM_DESC(idx, "Индекс в массиве");
MODULE_PARM_DESC(ch_val, "ASCII-код видимого символа");
MODULE_PARM_DESC(my_str, "Строка-результат");

static int __init hello_init(void)
{
	pr_info("init\n");
	memset(my_str, 'X', MY_STR_SIZE);
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
