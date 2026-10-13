/* func_ov004_022324f0 @ 0x022324f0, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565ec(void *arg);
extern int data_ov004_02255ab8;

void *func_ov004_022324f0(void *arg)
{
    func_020565ec(arg);
    *(void **) arg = &data_ov004_02255ab8;
    return arg;
}
