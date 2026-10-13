/* func_ov004_0222c0b8 @ 0x0222c0b8, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern void *func_02096718(int a);
extern int func_0200e828(void);
extern int func_ov004_02229774(void *p, int a, int b, short e, int f, int g, short h);

int func_ov004_0222c0b8(int *a, int *b, short *c, unsigned char *d)
{
    void *p = func_02096718(4);
    int n;

    if (p != 0) {
        n = 6;
        if (n <= func_0200e828()) {
            return 0;
        }
        return func_ov004_02229774(p, *a, *b, (short) (*c + 0x8000), d[0], n, -1);
    }
    return 0;
}
