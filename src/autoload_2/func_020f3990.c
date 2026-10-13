/* func_020f3990 @ 0x020f3990, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ea38;
extern void func_020f4514(void *);
extern void func_020edb3c(void *);

void *func_020f3990(void *arg)
{
    *(void **) arg = &data_0213ea38;
    func_020f4514(arg);
    func_020edb3c(arg);
    return arg;
}
