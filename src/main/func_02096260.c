/* func_02096260 @ 0x02096260, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021d56a4[];

char *func_02096260(int param)
{
    return &data_021d56a4[param * 4];
}
