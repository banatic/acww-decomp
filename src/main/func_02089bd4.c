/* func_02089bd4 @ 0x02089bd4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02089ca4(void *p);
extern int data_020e2044;

void *func_02089bd4(void *arg)
{
    func_02089ca4(arg);
    *(int *) arg = (int) &data_020e2044;
    return arg;
}
