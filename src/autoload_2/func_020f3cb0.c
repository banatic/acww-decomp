/* func_020f3cb0 @ 0x020f3cb0, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ec40;
extern void *func_020f3f14(void *);

void *func_020f3cb0(void *arg)
{
    *(void **) arg = &data_0213ec40;
    func_020f3f14(arg);
    return arg;
}
