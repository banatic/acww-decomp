/* func_ov114_0229c180 @ 0x0229c180, 0x10 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

void func_ov114_0229c180(unsigned short *p, unsigned short mask)
{
    unsigned short v;
    p = (unsigned short *) ((char *) p + 0x12ac);
    v = *p;
    v &= ~mask;
    *p = v;
}
