/* func_020617d8 @ 0x020617d8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020dded8[];

int func_020617d8(int r0)
{
    if (r0 < 0 || r0 > 0xb) {
        r0 = 0;
    }
    return data_020dded8[r0];
}
