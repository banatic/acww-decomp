/* func_ov004_022451fc @ 0x022451fc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022454fc(void *arg);
extern int data_ov004_022566d8;

void *func_ov004_022451fc(void *arg)
{
    func_ov004_022454fc(arg);
    *(void **) arg = &data_ov004_022566d8;
    return arg;
}
