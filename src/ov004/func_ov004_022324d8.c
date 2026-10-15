/* func_ov004_022324d8 @ 0x022324d8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255ab8;
extern void *func_02056578(void *);

void *func_ov004_022324d8(void *arg)
{
    *((void **) arg) = &data_ov004_02255ab8;
    func_02056578(arg);
    return arg;
}
