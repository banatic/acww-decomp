/* func_ov004_022254c4 @ 0x022254c4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020161ac(void *arg);
extern int data_ov004_02254888;

void *func_ov004_022254c4(void *arg)
{
    func_020161ac(arg);
    *(void **) arg = &data_ov004_02254888;
    return arg;
}
