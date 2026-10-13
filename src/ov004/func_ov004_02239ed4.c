/* func_ov004_02239ed4 @ 0x02239ed4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255d54;
extern void func_ov004_0223a374(void *);

void *func_ov004_02239ed4(void *arg)
{
    *((void **) arg) = &data_ov004_02255d54;
    func_ov004_0223a374(arg);
    return arg;
}
