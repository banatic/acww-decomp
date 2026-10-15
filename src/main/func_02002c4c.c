/* func_02002c4c @ 0x02002c4c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002c6c(int, int, int, int, int, int);

int func_02002c4c(int a1, int a2, int a3, int a4, int a5, int a6)
{
    int local0;
    int local1;

    local0 = a5 << 1;
    local1 = (a6 << 1) + 1;
    return func_02002c6c(a1, a2, a3, a4 << 1, local0, local1);
}
