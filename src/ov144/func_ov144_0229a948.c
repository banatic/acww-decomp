/* func_ov144_0229a948 @ 0x0229a948, 0x68 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *);
extern int func_ov144_0229a17c(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_022080a0(void *, int);

void func_ov144_0229a948(void *self)
{
    if (func_ov002_0220a700((char *) self + 0x170)) {
        if (func_0208e4bc((char *) self + 0xc4)) {
            int r4 = func_ov002_0220a6e0((char *) self + 0x170);
            int r6 = func_ov002_0220a768((char *) self + 0x170, -1);
            int r2 = func_ov002_0220a72c((char *) self + 0x170, -1);
            func_ov002_0220a0b4((char *) self + 0xc4, r4 + r6, r4 + r2);
        }
    } else {
        func_ov144_0229a17c(self);
        func_ov002_022080a0(self, 1);
    }
}
