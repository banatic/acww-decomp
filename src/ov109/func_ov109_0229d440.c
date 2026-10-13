/* func_ov109_0229d440 @ 0x0229d440, 0x38 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov109_0229c988(void *);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);

void func_ov109_0229d440(void *self)
{
    func_ov002_022091cc((char *) self + 0x22d8);
    func_ov094_0229a05c((char *) self + 0xb54);
    if (func_ov002_02207d5c((char *) self + 0x218c)) {
        func_ov109_0229c988(self);
    }
}
