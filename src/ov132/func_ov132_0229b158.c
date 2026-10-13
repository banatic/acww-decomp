/* func_ov132_0229b158 @ 0x0229b158, 0x2c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(char *p, int n);
extern void func_ov132_0229b104(char *p);
extern void func_0208e5cc(char *p);

void func_ov132_0229b158(char *p)
{
    if (func_ov002_0220b8ac(p + 0x3e4, 0)) {
        func_ov132_0229b104(p);
        p += 0x94;
        func_0208e5cc(p);
    }
}
