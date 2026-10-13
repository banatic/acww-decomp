/* func_ov004_0221f848 @ 0x0221f848, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02253b24;
extern void func_0202de4c(void *);

void *func_ov004_0221f848(void *arg)
{
    *((void **) arg) = &data_ov004_02253b24;
    func_0202de4c(arg);
    return arg;
}
