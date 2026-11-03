/* c_library: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02064310 @ 0x02064310, 0x18 bytes, Thumb
 * func_02064300 @ 0x02064300, 0xe bytes, Thumb
 */

extern int OS_VSNPrintf(int a, int b, int c, int d);

int func_02064300(int a, int b, int c, int d);

int func_02064310(int a, int b, int c)
{
    return func_02064300(a, 0x7fffffff, b, c);
}

int func_02064300(int a, int b, int c, int d)
{
    return OS_VSNPrintf(a, b, c, d);
}
