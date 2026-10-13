/* func_ov004_022219ac @ 0x022219ac, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202decc(void *arg);
extern int data_ov004_02253f44;

void *func_ov004_022219ac(void *arg)
{
    func_0202decc(arg);
    *(void **) arg = &data_ov004_02253f44;
    return arg;
}
