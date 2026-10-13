/* func_0206f56c @ 0x0206f56c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021cfc54;
extern int func_0206fec8(int param);

int func_0206f56c(void)
{
    int result;

    if (data_021cfc54 != 0) {
        result = 0;
    } else {
        result = func_0206fec8(0x80);
    }

    return result;
}
