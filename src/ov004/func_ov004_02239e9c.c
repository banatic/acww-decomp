/* func_ov004_02239e9c @ 0x02239e9c, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223a458(void *arg);
extern int data_ov004_02255d3c;

void *func_ov004_02239e9c(void *arg)
{
    func_ov004_0223a458(arg);
    *(void **) arg = &data_ov004_02255d3c;
    return arg;
}
