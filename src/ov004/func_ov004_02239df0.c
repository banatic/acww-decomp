/* func_ov004_02239df0 @ 0x02239df0, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223a5e4(void *arg);
extern int data_ov004_02255e2c;

void *func_ov004_02239df0(void *arg)
{
    func_ov004_0223a5e4(arg);
    *(void **) arg = &data_ov004_02255e2c;
    return arg;
}
