/* func_ov099_0229d8d8 @ 0x0229d8d8, 0x38 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov099_0229ca34(void *);

void func_ov099_0229d8d8(char *self)
{
    func_ov002_022091cc(self + 0x22d8);
    func_ov094_0229a05c(self + 0xb54);
    if (func_ov002_02207d5c(self + 0x218c) != 0) {
        func_ov099_0229ca34(self);
    }
}
