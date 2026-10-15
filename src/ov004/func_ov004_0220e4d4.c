/* func_ov004_0220e4d4 @ 0x0220e4d4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_0224fe44;
extern void *func_02056578(void *);

void *func_ov004_0220e4d4(void *arg)
{
    *((void **) arg) = &data_ov004_0224fe44;
    func_02056578(arg);
    return arg;
}
