/* func_ov132_0229b1b0 @ 0x0229b1b0, 0x62 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(unsigned char *);
extern int func_0208e4bc(unsigned char *);
extern int func_ov002_0220a6e0(unsigned char *);
extern int func_ov002_0220a768(unsigned char *, int);
extern int func_ov002_0220a72c(unsigned char *, int);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov132_0229ae90(unsigned char *);
extern void func_ov002_022080a0(unsigned char *, int);

void func_ov132_0229b1b0(unsigned char *base)
{
    if (func_ov002_0220a700(base + 0xf8)) {
        if (func_0208e4bc(base + 0x94)) {
            int a;
            int b;
            int c;

            a = func_ov002_0220a6e0(base + 0xf8);
            b = func_ov002_0220a768(base + 0xf8, -1);
            c = func_ov002_0220a72c(base + 0xf8, -1);
            base += 0x94;
            func_ov002_0220a0b4(base, a + b, a + c);
        }
    } else {
        func_ov132_0229ae90(base);
        func_ov002_022080a0(base, 1);
    }
}
