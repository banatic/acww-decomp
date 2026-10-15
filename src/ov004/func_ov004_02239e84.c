/* func_ov004_02239e84 @ 0x02239e84, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255d3c;
extern void *func_ov004_0223a374(void *);

void *func_ov004_02239e84(void *arg)
{
    *((void **) arg) = &data_ov004_02255d3c;
    func_ov004_0223a374(arg);
    return arg;
}
