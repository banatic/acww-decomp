/* func_02031d48 @ 0x02031d48, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c9088[];

int func_02031d48(int r0)
{
    if (r0 < 0x7c) {
        return data_020c9088[r0 * 30];
    }
    return 0;
}
