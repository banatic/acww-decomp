/* func_ov106_0229e928 @ 0x0229e928, 0x38 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov106_0229cf0c(void *);

void func_ov106_0229e928(void *self)
{
    func_ov002_022091cc((char *) self + 0x2304);
    func_ov094_0229a05c((char *) self + 0xb80);
    if (func_ov002_02207d5c((char *) self + 0x21b8)) {
        func_ov106_0229cf0c(self);
    }
}
