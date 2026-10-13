/* func_02096244 @ 0x02096244, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021d56b8[]; // 0x021d56b8

int func_02096244(int a)
{
    return (int) &data_021d56b8[a * 12];
}
