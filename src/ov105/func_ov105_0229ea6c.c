/* func_ov105_0229ea6c @ 0x0229ea6c, 0x38 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229d294(void *);
extern int func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern int func_ov002_022091cc(void *);

void func_ov105_0229ea6c(void *self)
{
    func_ov002_022091cc((char *) self + 0x2508);
    func_ov094_0229a05c((char *) self + 0xd84);
    if (func_ov002_02207d5c((char *) self + 0x23bc)) {
        func_ov105_0229d294(self);
    }
}
