/* func_ov110_0229cff8 @ 0x0229cff8, 0x5c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d5e4(void *, void *);
extern int func_ov110_0229d5d4(void *, void *);
extern int func_ov110_0229d590(void *, void *);
extern void func_ov094_0229ab1c(void *, int);
extern void func_ov094_0229b98c(void *);
extern int func_ov110_0229d5c8(void *, void *);
extern void func_ov110_0229d054(void *);

void func_ov110_0229cff8(void *self, void *param2)
{
    if (func_ov110_0229d5e4(self, param2) != 0 || func_ov110_0229d5d4(self, param2) != 0) {
        int r = func_ov110_0229d590(self, param2);
        func_ov094_0229ab1c((char *) self + 0x138, r);
        func_ov094_0229b98c((char *) self + 0xb98);
    } else {
        if (func_ov110_0229d5c8(self, param2) != 0) {
            func_ov110_0229d054(self);
        }
    }
}
