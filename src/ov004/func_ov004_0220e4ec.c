/* func_ov004_0220e4ec @ 0x0220e4ec, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565ec(void *arg);
extern int data_ov004_0224fe44;

void *func_ov004_0220e4ec(void *arg)
{
    func_020565ec(arg);
    *(void **) arg = &data_ov004_0224fe44;
    return arg;
}
