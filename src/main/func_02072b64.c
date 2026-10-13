/* func_02072b64 @ 0x02072b64, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_02072b64(unsigned char *r0, int r1);

unsigned char func_02072b64(unsigned char *r0, int r1)
{
    unsigned char r0_val;
    int r2;

    r2 = 7;
    r1 &= r2;
    r0_val = r0[r1];
    r0_val &= r2;
    return r0_val;
}
