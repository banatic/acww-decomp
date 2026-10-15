/* func_ov004_02222efc @ 0x02222efc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_022543cc;
extern void *func_0202eb20(void *);

void *func_ov004_02222efc(void *arg)
{
    *((void **) arg) = &data_ov004_022543cc;
    func_0202eb20(arg);
    return arg;
}
