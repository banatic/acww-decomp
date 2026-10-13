/* func_ov055_02260a40 @ 0x02260a40, 0x18 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov055_02260f44;
extern void func_0202eb20(void *, void *);

void *func_ov055_02260a40(void *arg)
{
    void *p = &data_ov055_02260f44;
    *(void **) arg = p;
    func_0202eb20(arg, p);
    return arg;
}
