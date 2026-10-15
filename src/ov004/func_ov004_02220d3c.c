/* func_ov004_02220d3c @ 0x02220d3c, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202decc(void *arg);
extern int data_ov004_02253d80;

void *func_ov004_02220d3c(void *arg)
{
    func_0202decc(arg);
    *(void **) arg = &data_ov004_02253d80;
    return arg;
}
