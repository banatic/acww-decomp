/* func_ov004_02220d24 @ 0x02220d24, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02253d80;
extern void func_0202de4c(void *);

void *func_ov004_02220d24(void *arg)
{
    *((void **) arg) = &data_ov004_02253d80;
    func_0202de4c(arg);
    return arg;
}
