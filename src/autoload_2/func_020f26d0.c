/* func_020f26d0 @ 0x020f26d0, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern void func_020edb3c(void *);

extern unsigned char data_0213eee4[];

void *func_020f26d0(void *arg)
{
    *((int *) arg) = (unsigned int) data_0213eee4;
    func_020f4514(arg);
    func_020edb3c(arg);
    return arg;
}
