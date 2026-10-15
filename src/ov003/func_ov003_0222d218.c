/* func_ov003_0222d218 @ 0x0222d218, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c0ec;
extern void *func_02056578(void *);

void *func_ov003_0222d218(void *arg)
{
    *((void **) arg) = &data_ov003_0223c0ec;
    func_02056578(arg);
    return arg;
}
