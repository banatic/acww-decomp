/* func_02031d78 @ 0x02031d78, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c908a[];

int func_02031d78(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908a[r0 * 0x1e];
    }
    return 0;
}
