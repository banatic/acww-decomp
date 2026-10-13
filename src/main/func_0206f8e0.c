/* func_0206f8e0 @ 0x0206f8e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc68;

int func_0206f8e0(void)
{
    unsigned short v = data_021cfc68;
    if (v & 2) {
        return 2;
    }
    if (v & 1) {
        return 1;
    }
    if (v & 0x800) {
        return 3;
    }
    return 0;
}
