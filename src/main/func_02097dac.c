/* func_02097dac @ 0x02097dac, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02097dac(unsigned char *r0)
{
    unsigned char *p;
    int i;

    r0[0] = 1;
    r0[1] = 1;
    r0[2] = 0;
    r0[3] = 0;

    for (i = 0; i < 0xf; i++) {
        p = r0 + i;
        p[4] = 0;
    }

    r0[3] = 0x64;
}
