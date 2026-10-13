/* func_020f2e18 @ 0x020f2e18, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ed10;
extern void func_020f4514(void *);

void *func_020f2e18(void *arg)
{
    *(int **) arg = &data_0213ed10;
    func_020f4514(arg);
    return arg;
}
