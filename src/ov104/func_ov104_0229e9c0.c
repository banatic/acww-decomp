/* func_ov104_0229e9c0 @ 0x0229e9c0, 0x38 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d624(void *);
extern int func_ov094_0229a05c(void *);
extern int func_ov002_022091cc(void *);
extern int func_ov002_02207d5c(void *);

void func_ov104_0229e9c0(void *self)
{
    func_ov002_022091cc((char *) self + 0x2504);
    func_ov094_0229a05c((char *) self + 0xd80);
    if (func_ov002_02207d5c((char *) self + 0x23b8)) {
        func_ov104_0229d624(self);
    }
}
