/* func_020e92e8 @ 0x020e92e8, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020e92e8(unsigned int *r0);

unsigned int func_020e92e8(unsigned int *r0)
{
    unsigned int r3;
    unsigned int r1;
    unsigned int r2;
    unsigned int result;

    r3 = *r0;
    r1 = 0x0019660d;
    r2 = 0x3c6ef35f;
    r1 = r3 * r1 + r2;
    *r0 = r1;
    result = *r0;
    return result;
}
