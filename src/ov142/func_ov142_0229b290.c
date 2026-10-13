/* func_ov142_0229b290 @ 0x0229b290, 0x68 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *);
extern int func_ov142_0229af94(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_022080a0(void *, int);

void func_ov142_0229b290(void *self)
{
    int r4, r6;
    int r2;

    if (func_ov002_0220a700((char *) self + 0x194)) {
        if (func_0208e4bc((char *) self + 0xe8)) {
            r4 = func_ov002_0220a6e0((char *) self + 0x194);
            r6 = func_ov002_0220a768((char *) self + 0x194, -1);
            r2 = func_ov002_0220a72c((char *) self + 0x194, -1);
            func_ov002_0220a0b4((char *) self + 0xe8, r4 + r6, r4 + r2);
        }
    } else {
        func_ov142_0229af94(self);
        func_ov002_022080a0(self, 1);
    }
}
