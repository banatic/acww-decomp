/* func_ov137_0229c554 @ 0x0229c554, 0x10 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

void func_ov137_0229c554(unsigned short *base, unsigned short mask)
{
    base = (unsigned short *) ((char *) base + 0x2b74);
    *base &= ~mask;
}
