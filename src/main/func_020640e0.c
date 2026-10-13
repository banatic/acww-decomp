/* func_020640e0 @ 0x020640e0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cca9c[];

unsigned char *func_020640e0(unsigned char *p)
{
    if (*p >= 6) {
        *p = *p % 6;
    }
    return data_020cca9c + *p * 3;
}
