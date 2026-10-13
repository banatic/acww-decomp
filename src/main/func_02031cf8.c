/* func_02031cf8 @ 0x02031cf8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c908e[];

unsigned char func_02031cf8(int x)
{
    if (x < 124) {
        return data_020c908e[x * 30];
    }
    return 0;
}
