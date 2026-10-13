/* func_ov131_0229b124 @ 0x0229b124, 0x62 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(char *p);
extern int func_0208e4bc(char *p);
extern int func_ov002_0220a6e0(char *p);
extern int func_ov002_0220a768(char *p, int x);
extern int func_ov002_0220a72c(char *p, int x);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov131_0229afbc(void *p);
extern void func_ov002_022080a0(void *p, int x);

void func_ov131_0229b124(void *arg)
{
    if (func_ov002_0220a700((char *) arg + 0xf8) != 0) {
        if (func_0208e4bc((char *) arg + 0x94) != 0) {
            int r4, r6, r2;

            r4 = func_ov002_0220a6e0((char *) arg + 0xf8);
            r6 = func_ov002_0220a768((char *) arg + 0xf8, -1);
            r2 = func_ov002_0220a72c((char *) arg + 0xf8, -1);
            func_ov002_0220a0b4((char *) arg + 0x94, r4 + r6, r4 + r2);
        }
    } else {
        func_ov131_0229afbc(arg);
        func_ov002_022080a0(arg, 1);
    }
}
