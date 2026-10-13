/* func_ov003_0222d230 @ 0x0222d230, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565ec(void *arg);
extern int data_ov003_0223c0ec;

void *func_ov003_0222d230(void *arg)
{
    func_020565ec(arg);
    *(void **) arg = &data_ov003_0223c0ec;
    return arg;
}
