/* func_ov107_0229db7c @ 0x0229db7c, 0x38 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229cfe4(void *);
extern void func_ov002_022091cc(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);

void func_ov107_0229db7c(void *self)
{
    func_ov002_022091cc((char *) self + 0x2318);
    func_ov094_0229a05c((char *) self + 0xb94);
    if (func_ov002_02207d5c((char *) self + 0x21cc)) {
        func_ov107_0229cfe4(self);
    }
}
