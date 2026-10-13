/* func_ov113_0229a350 @ 0x0229a350, 0x40 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov113_02299da4(void *p, int a);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_ov113_02299d84(void *p, int a);

void func_ov113_0229a350(void *p)
{
    if (func_ov113_02299da4(p, 1)) {
        if (func_020b9bbc((char *) p + 0x26c4, (char *) p + 0xa0, 2, 0x800, 0)) {
            func_ov113_02299d84(p, 1);
        }
    }
}
