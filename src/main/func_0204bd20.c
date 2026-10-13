/* func_0204bd20 @ 0x0204bd20, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204bd20(unsigned int param0, unsigned int param1);

unsigned short func_0204bd20(unsigned int param0, unsigned int param1)
{
    unsigned int r2;
    unsigned int r1;
    unsigned int r0;

    if (param0 < 0x40) {
        r2 = param0 * 4 + 0x1000;
    } else {
        r2 = 0x1000;
    }

    r1 = param1 - 1;
    r0 = 3;
    r1 = r1 & r0;
    r0 = r1 + r2;
    r0 = r0 << 16;
    r0 = r0 >> 16;
    return (unsigned short) r0;
}
