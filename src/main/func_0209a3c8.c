/* func_0209a3c8 @ 0x0209a3c8, 0xb0 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_InvSqrt(int);

void func_0209a3c8(int *r4)
{
    int r0, r1, r2, r3;
    long long acc;
    int *p = r4;

    r0 = p[0];
    r1 = p[1];
    acc = (long long) r0 * r0;
    acc += (long long) r1 * r1;
    r1 = p[2];
    r0 = p[3];
    acc += (long long) r1 * r1;
    acc += (long long) r0 * r0;
    r0 = (int) (acc >> 12);
    r0 = FX_InvSqrt(r0);

    r2 = p[0];
    r1 = 0x800;
    acc = (long long) r0 * r2;
    acc += r1;
    r3 = (int) (acc >> 12);
    p[0] = r3;

    r2 = p[1];
    acc = (long long) r0 * r2;
    acc += r1;
    r3 = (int) (acc >> 12);
    p[1] = r3;

    r2 = p[2];
    acc = (long long) r0 * r2;
    acc += r1;
    r3 = (int) (acc >> 12);
    p[2] = r3;

    r2 = p[3];
    acc = (long long) r0 * r2;
    acc += r1;
    r1 = (int) (acc >> 12);
    p[3] = r1;
}