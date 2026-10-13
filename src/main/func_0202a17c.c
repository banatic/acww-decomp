/* func_0202a17c @ 0x0202a17c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0202a17c(unsigned short *param0, int param1);

unsigned short func_0202a17c(unsigned short *param0, int param1)
{
    unsigned short r4;
    unsigned short r3;
    unsigned short r2;
    unsigned short r0;

    r4 = 0;
    r3 = 0;
    r2 = *param0;
    if (r2 >= 0x12b0 && r2 <= 0x12e7) {
        r3 = 1;
    }
    if (r3 != 0 && param1 == 0) {
        r4 = 1;
    }
    return r4;
}
