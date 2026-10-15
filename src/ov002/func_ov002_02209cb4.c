/* func_ov002_02209cb4 @ 0x02209cb4, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bc50;
extern void *func_ov002_0220a39c(void *);

void *func_ov002_02209cb4(void *arg)
{
    *((void **) arg) = &data_ov002_0220bc50;
    func_ov002_0220a39c(arg);
    return arg;
}
