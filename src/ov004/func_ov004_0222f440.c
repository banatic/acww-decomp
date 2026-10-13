/* func_ov004_0222f440 @ 0x0222f440, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c87c(void *arg);
extern int data_ov004_02255290;

void *func_ov004_0222f440(void *arg)
{
    func_ov004_0222c87c(arg);
    *(void **) arg = &data_ov004_02255290;
    return arg;
}
