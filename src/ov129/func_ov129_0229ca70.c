/* func_ov129_0229ca70 @ 0x0229ca70, 0x6c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(unsigned char *);
extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220a6e0(unsigned char *);
extern int func_ov002_0220a768(unsigned char *, int);
extern int func_ov002_0220a72c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov129_0229c3f4(unsigned char *);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

void func_ov129_0229ca70(unsigned char *p)
{
    if (func_ov002_0220a700(p + 0x1d4)) {
        if (func_0208e4bc(p + 0x3a0)) {
            int a = func_ov002_0220a6e0(p + 0x1d4);
            int b = func_ov002_0220a768(p + 0x1d4, -1);
            int c = func_ov002_0220a72c(p + 0x1d4, -1);
            func_ov002_0220a0b4(p + 0x3a0, a + b, a + c);
        }
    } else {
        func_ov129_0229c3f4(p);
        func_ov002_022080a0((void *) (p), 1);
    }
}
