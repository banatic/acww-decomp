/* func_0206fec8 @ 0x0206fec8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc6c;

int func_0206fec8(unsigned int param)
{
    if ((param & data_021cfc6c) == param) {
        return 1;
    } else {
        return 0;
    }
}
