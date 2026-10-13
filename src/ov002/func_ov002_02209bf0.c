/* func_ov002_02209bf0 @ 0x02209bf0, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bba8;
extern void func_02070ba4(void *);

void *func_ov002_02209bf0(void *arg)
{
    *((void **) arg) = &data_ov002_0220bba8;
    func_02070ba4(arg);
    return arg;
}
