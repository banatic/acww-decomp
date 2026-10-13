/* func_02072380 @ 0x02072380, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021d054c[];

int func_02072380(int unused, int row, int col)
{
    int row_off = (row & 3) * 32;
    int col_off = (col & 7) * 4;
    return *(int *) (data_021d054c + row_off + col_off);
}
