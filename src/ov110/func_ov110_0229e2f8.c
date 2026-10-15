/* func_ov110_0229e2f8 @ 0x0229e2f8, 0x38 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229cea8(void *);
extern void func_ov094_0229a05c(void *);
extern void func_ov002_022091cc(void *);
extern int func_ov002_02207d5c(void *);

void func_ov110_0229e2f8(void *self)
{
    func_ov002_022091cc((char *) self + 0x2344);
    func_ov094_0229a05c((char *) self + 0xbc0);
    if (func_ov002_02207d5c((char *) self + 0x21f8)) {
        func_ov110_0229cea8(self);
    }
}
