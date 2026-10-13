/* func_ov112_022a0d6c @ 0x022a0d6c, 0xb8 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(const void *);
extern int func_ov002_02208008(const void *);
extern int func_ov095_02299a54(const void *, int);
extern void func_ov112_0229ff38(const void *);
extern void func_ov112_0229f35c(const void *);
extern void func_ov002_0220a2b4(const void *);
extern void func_ov002_0220a254(const void *);
extern void func_ov002_0220a314(const void *);
extern int func_ov112_022a0710(const void *);
extern int func_ov112_022a06b8(const void *);
extern int func_ov112_022a0620(const void *);
extern int func_ov112_022a0548(const void *);
extern int func_ov112_022a05b0(const void *);
extern int func_ov112_022a051c(const void *);

void func_ov112_022a0d6c(char *self)
{
    int v;

    if (func_ov002_02208014(self) != 0) {
        func_ov112_0229ff38(self);
        return;
    }

    v = func_ov095_02299a54(self + 0x384, func_ov002_02208008(self));

    switch (v) {
        case 1:
            func_ov002_0220a2b4(self + 0x4448);
            func_ov112_0229f35c(self);
            break;
        case 2:
            func_ov002_0220a254(self + 0x4448);
            func_ov112_0229f35c(self);
            break;
        case 3:
            func_ov002_0220a314(self + 0x4448);
            func_ov112_0229f35c(self);
            break;
        case 0:
        default:
            if (func_ov112_022a0710(self) != 0) {
                return;
            }
            if (func_ov112_022a06b8(self) != 0) {
                return;
            }
            if (func_ov112_022a0620(self) != 0) {
                return;
            }
            if (func_ov112_022a0548(self) != 0) {
                return;
            }
            if (func_ov112_022a05b0(self) != 0) {
                return;
            }
            if (func_ov112_022a051c(self) != 0) {
                return;
            }
    }
}
