/* func_ov114_0229c190 @ 0x0229c190, 0x10 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

void func_ov114_0229c190(unsigned short *p, unsigned short mask)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x12ac);
    *q = (unsigned short) (*q | mask);
}
