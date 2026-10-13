/* func_020e8840 @ 0x020e8840, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_020e8840(unsigned short *r0);

unsigned short func_020e8840(unsigned short *r0)
{
    unsigned short r1 = *r0;
    if (r1 != 0) {
        r1 = r1 - 1;
        *r0 = r1;
    }
    return *r0;
}
