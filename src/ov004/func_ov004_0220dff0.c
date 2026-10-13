/* func_ov004_0220dff0 @ 0x0220dff0, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_0224fe0c;
extern void func_0203248c(void *);

void *func_ov004_0220dff0(void *arg)
{
    *((void **) arg) = &data_ov004_0224fe0c;
    func_0203248c(arg);
    return arg;
}
