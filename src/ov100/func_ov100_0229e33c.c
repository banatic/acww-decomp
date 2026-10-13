/* func_ov100_0229e33c @ 0x0229e33c, 0x38 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229cf30(void *);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);

void func_ov100_0229e33c(void *self)
{
    func_ov002_022091cc((char *) self + 0x22d8);
    func_ov094_0229a05c((char *) self + 0xb54);
    if (func_ov002_02207d5c((char *) self + 0x218c)) {
        func_ov100_0229cf30(self);
    }
}
