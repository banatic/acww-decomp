/* func_ov004_022451e4 @ 0x022451e4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_022566d8;
extern void func_ov004_02245474(void *);

void *func_ov004_022451e4(void *arg)
{
    *((void **) arg) = &data_ov004_022566d8;
    func_ov004_02245474(arg);
    return arg;
}
