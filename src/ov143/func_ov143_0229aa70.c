/* func_ov143_0229aa70 @ 0x0229aa70, 0x3c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int n);
extern void func_ov002_02208090(void *p, int n);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern int func_ov002_0220a8e8(void *p, int n);
extern void func_ov143_02299680(void *p);

void func_ov143_0229aa70(void *p)
{
    if (func_ov002_02207f3c(p, -1)) {
        func_ov002_02208090(p, 5);
        func_ov002_02207eb4(p, 0, 0);
        func_ov002_0220a8e8((char *) p + 0x110, 0x8d);
        func_ov143_02299680(p);
    }
}
