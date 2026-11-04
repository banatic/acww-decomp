/* approach: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e8858 @ 0x020e8858, 0x18 bytes, ARM
 * func_020e8840 @ 0x020e8840, 0x18 bytes, ARM
 */

unsigned char func_020e8858(unsigned char *p)
{
    unsigned char c = *p;
    if (c != 0) {
        *p = c - 1;
    }
    return *p;
}

unsigned short func_020e8840(unsigned short *r0)
{
    unsigned short r1 = *r0;
    if (r1 != 0) {
        r1 = r1 - 1;
        *r0 = r1;
    }
    return *r0;
}
