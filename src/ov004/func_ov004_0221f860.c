/* func_ov004_0221f860 @ 0x0221f860, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202decc(void *arg);
extern int data_ov004_02253b24;

void *func_ov004_0221f860(void *arg)
{
    func_0202decc(arg);
    *(void **) arg = &data_ov004_02253b24;
    return arg;
}
