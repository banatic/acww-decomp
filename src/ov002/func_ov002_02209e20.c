/* func_ov002_02209e20 @ 0x02209e20, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bc40;
extern void func_020edb3c(void *);

void *func_ov002_02209e20(void *arg)
{
    *((void **) arg) = &data_ov002_0220bc40;
    func_020edb3c(arg);
    return arg;
}
