/* func_ov004_02221994 @ 0x02221994, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02253f44;
extern void func_0202de4c(void *);

void *func_ov004_02221994(void *arg)
{
    *((void **) arg) = &data_ov004_02253f44;
    func_0202de4c(arg);
    return arg;
}
