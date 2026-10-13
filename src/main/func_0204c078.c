/* func_0204c078 @ 0x0204c078, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204c078(unsigned int param);

unsigned short func_0204c078(unsigned int param)
{
    unsigned short result;
    unsigned int temp;

    if (param < 0x20) {
        temp = param + 0x1188;
        result = (unsigned short) (temp << 16 >> 16);
    } else {
        result = 0x1188;
    }
    return result;
}
