/* func_ov141_0229a280 @ 0x0229a280, 0x44 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov141_02299f7c(char *p, int a);
extern int func_020b9bbc(char *a, char *b, int c, int d, int e);
extern void func_ov141_02299f5c(char *p, int a);

void func_ov141_0229a280(char *p)
{
    if (func_ov141_02299f7c(p, 4)) {
        if (func_020b9bbc(p + 0xc68, p + 0x127c, 6, 0x800, 0)) {
            func_ov141_02299f5c(p, 4);
        }
    }
}
