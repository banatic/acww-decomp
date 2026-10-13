/* func_02079b08 @ 0x02079b08, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208090c(int);
extern unsigned char data_020cd484[][4];

unsigned char func_02079b08(int unused, int a, int b)
{
    unsigned char first = (unsigned char) (func_0208090c(a) & 3);
    unsigned char second = (unsigned char) (func_0208090c(b) & 3);
    return data_020cd484[first][second];
}
