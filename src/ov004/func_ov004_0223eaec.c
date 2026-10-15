/* func_ov004_0223eaec @ 0x0223eaec, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_022562b0;
extern void *func_02056578(void *);

void *func_ov004_0223eaec(void *arg)
{
    *((void **) arg) = &data_ov004_022562b0;
    func_02056578(arg);
    return arg;
}
