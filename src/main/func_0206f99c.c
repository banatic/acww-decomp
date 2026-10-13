/* func_0206f99c @ 0x0206f99c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int);
extern unsigned short data_021cfc68;

int func_0206f99c(void)
{
    if (func_0206fbf8(0x25) != 0) {
        data_021cfc68 = 0;
        return 1;
    } else {
        return 0;
    }
}
