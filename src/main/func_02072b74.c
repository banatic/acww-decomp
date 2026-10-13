/* func_02072b74 @ 0x02072b74, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02072b74(unsigned char *data, int a, int b)
{
    unsigned char tmp;
    tmp = data[a & 7];
    data[a & 7] = data[b & 7];
    data[b & 7] = tmp;
}
