/* func_ov004_0222c030 @ 0x0222c030, 0x3e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int k);
extern int func_ov004_02228628(void *p, int a, int b, int c, int d, int e, int f);

int func_ov004_0222c030(int *a, int *b, int *c, short *d)
{
    void *p = func_02096718(4);

    if (p != 0) {
        return func_ov004_02228628(p, (unsigned char) *a, *b, *c, *d, 6, -1);
    }
    return 0;
}
