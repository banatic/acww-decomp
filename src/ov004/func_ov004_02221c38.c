/* func_ov004_02221c38 @ 0x02221c38, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02254148;
extern void func_0202de4c(void *);

void *func_ov004_02221c38(void *arg)
{
    *((void **) arg) = &data_ov004_02254148;
    func_0202de4c(arg);
    return arg;
}
