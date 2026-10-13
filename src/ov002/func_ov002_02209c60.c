/* func_ov002_02209c60 @ 0x02209c60, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bc6c;
extern void func_ov002_0220a39c(void *);

void *func_ov002_02209c60(void *arg)
{
    *((void **) arg) = &data_ov002_0220bc6c;
    func_ov002_0220a39c(arg);
    return arg;
}
