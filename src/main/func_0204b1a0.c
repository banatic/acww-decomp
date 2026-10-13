/* func_0204b1a0 @ 0x0204b1a0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204b1a0(unsigned short arg0);

unsigned short func_0204b1a0(unsigned short arg0)
{
    unsigned short val;

    if (arg0 < 0x44) {
        val = (unsigned short) (arg0 + 0x1100);
    } else {
        val = 0x1100;
    }
    return val;
}
