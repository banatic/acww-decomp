/* func_02031d90 @ 0x02031d90, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c908b[];

int func_02031d90(int r0)
{
    if (r0 < 0x7c) {
        return data_020c908b[r0 * 30];
    }
    return 0;
}
