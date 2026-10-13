/* func_02031cc8 @ 0x02031cc8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c908c[];

unsigned char func_02031cc8(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908c[r0 * 30];
    }
    return 0;
}
