/* func_ov144_0229a83c @ 0x0229a83c, 0x2c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(char *, int);
extern void func_ov144_0229a7c8(char *);
extern void func_0208e5cc(char *);

void func_ov144_0229a83c(char *arg)
{
    char *p;

    p = arg;
    if (func_ov002_0220b8ac(p + 0x750, 1) != 0) {
        func_ov144_0229a7c8(p);
        p += 0xc4;
        func_0208e5cc(p);
    }
}
