/* func_0206f278 @ 0x0206f278, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned char data_021cfc14;

int func_0206f278(void)
{
    if ((data_021cfc14 & 1) != 0) {
        return 1;
    }
    return 0;
}
