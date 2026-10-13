/* func_0206f244 @ 0x0206f244, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short data_021cfc20;

int func_0206f244(void)
{
    unsigned short value;
    value = data_021cfc20;
    if (value == 0xc) {
        return 1;
    }
    return 0;
}
