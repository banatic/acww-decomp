/* func_ov004_02239c28 @ 0x02239c28, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02255d28;
extern void *func_02089b20(void *);

void *func_ov004_02239c28(void *arg)
{
    *((void **) arg) = &data_ov004_02255d28;
    func_02089b20(arg);
    return arg;
}
