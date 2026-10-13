/* func_ov144_0229aa70 @ 0x0229aa70, 0x4c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov144_0229a42c(char *p);
extern int func_ov144_0229a208(char *p);
extern int func_ov144_0229a198(char *p);
extern void func_ov144_0229a4b8(char *p);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov002_02208098(char *p, int n);

void func_ov144_0229aa70(char *p)
{
    int t;
    int x;
    int y;
    t = data_021fbe40 & 1;
    if (t != 0) {
        func_ov144_0229a42c(p);
        x = func_ov144_0229a208(p);
        y = func_ov144_0229a198(p);
        p += 0xc4;
        func_ov002_0220a0b4(p, x, y);
    } else {
        func_ov144_0229a4b8(p);
        func_ov002_02208098(p, 5);
    }
}
