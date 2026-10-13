/* func_0206f87c @ 0x0206f87c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc68;

int func_0206f87c(void)
{
    unsigned short value;
    unsigned int masked;

    value = data_021cfc68;
    masked = value & 0x00000100;
    if (masked != 0) {
        return 0;
    }
    return 1;
}
