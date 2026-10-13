/* func_02060e10 @ 0x02060e10, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_02060e10(unsigned int *arg0)
{
    unsigned int r0;
    unsigned int r1;

    r1 = 0x15a0;
    r0 = arg0[r1 >> 2];
    r0 = r0 << 0x16;
    r1 = r0 >> 0x1c;
    r1 = r1 & 0xf;
    r0 = r1 << 0x18;
    r0 = r0 >> 0x18;
    return r0;
}
