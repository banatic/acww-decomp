/* func_020addd0 @ 0x020addd0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020d1e3c[];

unsigned short func_020addd0(unsigned param)
{
    if (param < 5) {
        return data_020d1e3c[param];
    }
    return 0;
}
