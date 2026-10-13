/* func_020e8858 @ 0x020e8858, 0x18 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020e8858(unsigned char *p);

unsigned char func_020e8858(unsigned char *p)
{
    unsigned char c = *p;
    if (c != 0) {
        *p = c - 1;
    }
    return *p;
}
