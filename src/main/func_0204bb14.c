/* func_0204bb14 @ 0x0204bb14, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204bb14(unsigned int r0);

unsigned short func_0204bb14(unsigned int r0)
{
    if (r0 < 3U) {
        r0 += 0xb001;
    } else {
        r0 = 0xb001;
    }
    return (unsigned short) (r0 & 0xffff);
}
