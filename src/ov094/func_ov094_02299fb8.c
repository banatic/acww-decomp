/* func_ov094_02299fb8 @ 0x02299fb8, 0x40 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_022999b0(void *a, int b);
extern void func_ov094_022999a0(void *a, int b);
extern int func_020b9bbc(void *a, void *b, unsigned char c, int d, int e);

void func_ov094_02299fb8(void *p)
{
    if (func_ov094_022999b0(p, 1)) {
        if (func_020b9bbc((char *) p + 0x38, (char *) p + 0x1b8, ((unsigned char *) p)[0xe], 0x800, 0)) {
            func_ov094_022999a0(p, 1);
        }
    }
}
