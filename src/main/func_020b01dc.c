/* func_020b01dc @ 0x020b01dc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b01f0(void *);

int func_020b01dc(unsigned char *r0)
{
    unsigned char r2;
    unsigned char r1;

    r2 = r0[1];
    r1 = r0[0];
    if (r2 < r1) {
        r1 = r2 + 1;
        r0[1] = r1;
    }
    return func_020b01f0(r0);
}
