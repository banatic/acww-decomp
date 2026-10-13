/* func_ov004_0223a084 @ 0x0223a084, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255de4;
extern void func_ov004_0223a374(void *);

void *func_ov004_0223a084(void *arg)
{
    *((void **) arg) = &data_ov004_02255de4;
    func_ov004_0223a374(arg);
    return arg;
}
