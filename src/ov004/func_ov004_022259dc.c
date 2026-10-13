/* func_ov004_022259dc @ 0x022259dc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02254a38;
extern void func_0202ee5c(void *);

void *func_ov004_022259dc(void *arg)
{
    *((void **) arg) = &data_ov004_02254a38;
    func_0202ee5c(arg);
    return arg;
}
