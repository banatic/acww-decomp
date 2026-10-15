/* func_ov106_0229d860 @ 0x0229d860, 0x80 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(unsigned char *);
extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220a6e0(unsigned char *);
extern int func_ov002_0220a768(unsigned char *, int);
extern int func_ov002_0220a72c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov106_0229cc50(unsigned char *);
extern void func_ov106_0229c344(unsigned char *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

void func_ov106_0229d860(unsigned char *p)
{
    if (func_ov002_0220a700(p + 0x3fb4) != 0) {
        if (func_0208e4bc(p + 0x22a0) != 0) {
            int a = func_ov002_0220a6e0(p + 0x3fb4);
            int b = func_ov002_0220a768(p + 0x3fb4, -1);
            int c = func_ov002_0220a72c(p + 0x3fb4, -1);
            func_ov002_0220a0b4(p + 0x22a0, a + b, a + c);
        }
    } else {
        func_ov106_0229cc50(p);
        p[0x8c] = 4;
        func_ov106_0229c344(p, 0x100);
        func_ov002_022080a0((void *) (p), 1);
    }
}
