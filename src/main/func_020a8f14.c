/* func_020a8f14 @ 0x020a8f14, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02050c84(void *);
extern int data_020e3dac;

void *func_020a8f14(void *arg)
{
    *(int *) arg = (int) &data_020e3dac;
    func_02050c84(arg);
    return arg;
}
