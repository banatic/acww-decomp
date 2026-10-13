/* func_ov004_0223a028 @ 0x0223a028, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255e8c;
extern void func_ov004_0223a4ec(void *);

void *func_ov004_0223a028(void *arg)
{
    *((void **) arg) = &data_ov004_02255e8c;
    func_ov004_0223a4ec(arg);
    return arg;
}
