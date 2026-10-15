/* func_02093880 @ 0x02093880, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e2854[];
extern int func_02094b58(int a, int b, int c, int d, int e, int f);

int func_02093880(int a, int b, int c, int d, int e)
{
    unsigned int local0;
    unsigned int local1;

    local0 = d;
    local1 = (unsigned int) data_020e2854;
    return func_02094b58(0x73, a, b, c, local0, local1);
}
