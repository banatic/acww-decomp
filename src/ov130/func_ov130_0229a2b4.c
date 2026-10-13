/* func_ov130_0229a2b4 @ 0x0229a2b4, 0x78 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov130_022999b0(void *p, int n);
extern void func_ov130_022999a0(void *p, int n);
extern int func_020b9bbc(void *d, void *s, unsigned char c, int size, int opt);

void func_ov130_0229a2b4(void *p)
{
    if (func_ov130_022999b0(p, 1)) {
        if (func_020b9bbc((char *) p + 0x248, (char *) p + 0x290, ((unsigned char *) p)[0xa], 0x800, 0)) {
            func_ov130_022999a0(p, 1);
        }
    }
    if (func_ov130_022999b0(p, 2)) {
        if (func_020b9bbc((char *) p + 0x26c, (char *) p + 0xa90, ((unsigned char *) p)[0xb], 0x800, 0)) {
            func_ov130_022999a0(p, 2);
        }
    }
}
