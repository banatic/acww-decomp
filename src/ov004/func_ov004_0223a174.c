/* func_ov004_0223a174 @ 0x0223a174, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255e44;
extern void func_ov004_0223a4ec(void *);

void *func_ov004_0223a174(void *arg)
{
    *((void **) arg) = &data_ov004_02255e44;
    func_ov004_0223a4ec(arg);
    return arg;
}
