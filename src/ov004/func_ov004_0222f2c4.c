/* func_ov004_0222f2c4 @ 0x0222f2c4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255200;
extern void *func_ov004_0222c7a0(void *);

void *func_ov004_0222f2c4(void *arg)
{
    *((void **) arg) = &data_ov004_02255200;
    func_ov004_0222c7a0(arg);
    return arg;
}
