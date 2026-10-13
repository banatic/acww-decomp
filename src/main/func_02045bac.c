/* func_02045bac @ 0x02045bac, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021c7884[];

int func_02045bac(int index)
{
    return (int) (data_021c7884 + (index << 4));
}
