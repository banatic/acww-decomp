/* func_02072370 @ 0x02072370, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d04e4[];

int func_02072370(int unused, unsigned int index)
{
    return data_021d04e4[index & 7];
}
