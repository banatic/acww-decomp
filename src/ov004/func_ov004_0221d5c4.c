/* func_ov004_0221d5c4 @ 0x0221d5c4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_022537d8;
extern void func_0202de4c(void *);

void *func_ov004_0221d5c4(void *arg)
{
    *((void **) arg) = &data_ov004_022537d8;
    func_0202de4c(arg);
    return arg;
}
