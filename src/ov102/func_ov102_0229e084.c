/* func_ov102_0229e084 @ 0x0229e084, 0x2c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229ce58(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov094_0229a05c(void *);

void func_ov102_0229e084(void *self)
{
    func_ov094_0229a05c((char *) self + 0xb54);
    if (func_ov002_02207d5c((char *) self + 0x218c)) {
        func_ov102_0229ce58(self);
    }
}
