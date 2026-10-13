/* func_ov142_0229a540 @ 0x0229a540, 0x8c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_02299668(char *p, int a);
extern void func_ov142_0229a3c0(char *p);
extern void func_ov142_02299648(char *p, int a);
extern void func_ov142_0229ad74(char *p);
extern void func_ov142_0229ace4(char *p);
extern int func_020b9bbc(char *p1, char *p2, int a, int b, int c);

void func_ov142_0229a540(char *p)
{
    if (func_ov142_02299668(p, 2)) {
        func_ov142_0229a3c0(p);
    }
    if (func_ov142_02299668(p, 0x10)) {
        if (func_020b9bbc(p + 0x96c, p + 0x2860, 6, 0x800, 0)) {
            func_ov142_02299648(p, 0x10);
        }
    }
    if (func_ov142_02299668(p, 4)) {
        func_ov142_02299648(p, 4);
        func_ov142_0229ad74(p);
    }
    if (func_ov142_02299668(p, 8)) {
        func_ov142_02299648(p, 8);
        func_ov142_0229ace4(p);
    }
}
