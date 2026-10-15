/* func_ov004_02224598 @ 0x02224598, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020161ac(void *arg);
extern int data_ov004_02254650;

void *func_ov004_02224598(void *arg)
{
    func_020161ac(arg);
    *(void **) arg = &data_ov004_02254650;
    return arg;
}
