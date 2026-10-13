/* func_ov145_0229a370 @ 0x0229a370, 0x68 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *);
extern int func_ov145_02299ed0(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_022080a0(void *, int);

void func_ov145_0229a370(void *self)
{
    int r4, r6;
    int r2;
    void *p;

    if (func_ov002_0220a700((char *) self + 0x174) != 0) {
        if (func_0208e4bc((char *) self + 0xc8) != 0) {
            r4 = func_ov002_0220a6e0((char *) self + 0x174);
            r6 = func_ov002_0220a768((char *) self + 0x174, -1);
            r2 = func_ov002_0220a72c((char *) self + 0x174, -1);
            p = (char *) self + 0xc8;
            func_ov002_0220a0b4(p, r4 + r6, r4 + r2);
        }
    } else {
        func_ov145_02299ed0(self);
        func_ov002_022080a0(self, 1);
    }
}
