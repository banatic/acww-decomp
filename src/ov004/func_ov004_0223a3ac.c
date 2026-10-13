/* func_ov004_0223a3ac @ 0x0223a3ac, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255ea4;
extern void func_ov004_0223a4ec(void *);

void *func_ov004_0223a3ac(void *arg)
{
    *((void **) arg) = &data_ov004_02255ea4;
    func_ov004_0223a4ec(arg);
    return arg;
}
