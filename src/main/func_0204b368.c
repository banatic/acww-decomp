/* func_0204b368 @ 0x0204b368, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204b368(unsigned short param);

unsigned short func_0204b368(unsigned short param)
{
    if (param < 0x100) {
        return (unsigned short) (param + 0x11a8);
    }
    return 0x11a8;
}
