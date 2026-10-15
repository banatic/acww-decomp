/* func_ov004_0222f2dc @ 0x0222f2dc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0222c87c(void *arg);
extern int data_ov004_02255200;

void *func_ov004_0222f2dc(void *arg)
{
    func_ov004_0222c87c(arg);
    *(void **) arg = &data_ov004_02255200;
    return arg;
}
