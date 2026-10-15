/* func_ov004_02239dd8 @ 0x02239dd8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255e2c;
extern void *func_ov004_0223a4ec(void *);

void *func_ov004_02239dd8(void *arg)
{
    *((void **) arg) = &data_ov004_02255e2c;
    func_ov004_0223a4ec(arg);
    return arg;
}
