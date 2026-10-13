/* func_02031d60 @ 0x02031d60, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c9089[];

unsigned char func_02031d60(int r0)
{
    if (r0 < 0x7c) {
        return data_020c9089[r0 * 30];
    }
    return 0;
}
