/* func_020eaca0 @ 0x020eaca0, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eaca0(int *r0, int *r1, int *r2);

void func_020eaca0(int *r0, int *r1, int *r2)
{
    int a, b, c, d, e, f;

    a = r1[0];
    b = r2[0];
    c = r1[2];
    d = r2[2];
    e = r1[1];
    f = r2[1];

    r0[0] = a - b;
    r0[1] = e - f;
    r0[2] = c - d;
}
