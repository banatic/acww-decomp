/* func_ov108_0229d884 @ 0x0229d884, 0x38 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov108_0229ca2c(void *p);
extern void func_ov002_022091cc(void *p);
extern void func_ov094_0229a05c(void *p);
extern int func_ov002_02207d5c(void *p);

void func_ov108_0229d884(void *self)
{
    func_ov002_022091cc((char *) self + 0x24fc);
    func_ov094_0229a05c((char *) self + 0x0d78);
    if (func_ov002_02207d5c((char *) self + 0x23b0)) {
        func_ov108_0229ca2c(self);
    }
}
