/* func_02090078 @ 0x02090078, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021d36d4[];

int func_02090078(int index)
{
    return (int) (data_021d36d4 + 0x950 * index);
}
