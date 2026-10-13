/* func_ov094_0229a600 @ 0x0229a600, 0x34 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_020896b8(int a, int *b, int c, int d, int e, int f, int g);
extern int data_ov094_0229bfa0[];

int func_ov094_0229a600(int *p, int b, int c)
{
    return func_020896b8(1, data_ov094_0229bfa0, b - 8, c - 8, -1, p[0x294], 0);
}
