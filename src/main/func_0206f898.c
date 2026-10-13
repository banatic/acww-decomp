/* func_0206f898 @ 0x0206f898, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc68;

int func_0206f898(void)
{
    unsigned short value;
    unsigned short mask;
    int result;

    value = data_021cfc68;
    mask = 0x0400;
    if ((value & mask) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
