/* func_020bef88 @ 0x020bef88, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int DC_FlushRange(int a, int b);

int func_020bef88(int a)
{
    return DC_FlushRange(a + 0x448, 0xc00);
}
