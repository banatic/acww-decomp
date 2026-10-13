/* func_ov144_0229a12c @ 0x0229a12c, 0x4e bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a2b4(void *p);
extern int func_ov144_0229a208(void *self);
extern int func_ov144_0229a198(void *self);
extern void func_ov144_0229a0fc(void *self, int a, int b);

void func_ov144_0229a12c(void *self)
{
    unsigned char val;
    int a;
    int b;
    val = *(unsigned char *) ((char *) self + 0xc1);
    if (val == 9) {
        func_ov002_0220a314((char *) self + 0xc4);
    } else if (val <= 8) {
        func_ov002_0220a314((char *) self + 0xc4);
    } else {
        func_ov002_0220a2b4((char *) self + 0xc4);
    }
    a = func_ov144_0229a208(self);
    b = func_ov144_0229a198(self);
    func_ov144_0229a0fc(self, a, b);
}
