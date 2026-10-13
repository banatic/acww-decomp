/* func_02057cf4 @ 0x02057cf4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021c9350;

unsigned char func_02057cf4(void)
{
    if (data_021c9350 != 0) {
        return data_021c9350[0x58];
    }
    return 0xc;
}
