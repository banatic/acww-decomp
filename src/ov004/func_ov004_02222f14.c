/* func_ov004_02222f14 @ 0x02222f14, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *arg);
extern int data_ov004_022543cc;

void *func_ov004_02222f14(void *arg)
{
    func_0202eb70(arg);
    *(void **) arg = &data_ov004_022543cc;
    return arg;
}
