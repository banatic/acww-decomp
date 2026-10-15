/* func_ov137_0229ca2c @ 0x0229ca2c, 0x62 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(void *ptr);
extern int func_0208e4bc(void *ptr);
extern int func_ov002_0220a6e0(void *ptr);
extern int func_ov002_0220a768(void *ptr, int);
extern int func_ov002_0220a72c(void *ptr, int);
extern void func_ov002_0220a0b4(void *ptr, int, int);
extern unsigned char *func_ov002_022080a0(void *ptr, unsigned char value);
extern void func_ov137_0229c734(void *ptr);

void func_ov137_0229ca2c(char *p)
{
    int a, b, c;

    if (func_ov002_0220a700(p + 0xf8)) {
        if (func_0208e4bc(p + 0x94) == 0) {
            return;
        }
        a = func_ov002_0220a6e0(p + 0xf8);
        b = func_ov002_0220a768(p + 0xf8, -1);
        c = func_ov002_0220a72c(p + 0xf8, -1);
        p += 0x94;
        func_ov002_0220a0b4(p, a + b, a + c);
    } else {
        func_ov137_0229c734(p);
        func_ov002_022080a0(p, 1);
    }
}
