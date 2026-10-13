/* func_0204b1b8 @ 0x0204b1b8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204b1b8(unsigned int param);

unsigned short func_0204b1b8(unsigned int param)
{
    unsigned short result;

    if (param < 0x20) {
        result = (unsigned short) (param + 0x1380);
    } else {
        result = 0x1380;
    }

    return result;
}
