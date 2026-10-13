/* func_02031ce0 @ 0x02031ce0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c908d[];

int func_02031ce0(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908d[r0 * 0x1e];
    }
    return 0;
}
