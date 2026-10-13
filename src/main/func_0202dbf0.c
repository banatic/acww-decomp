/* func_0202dbf0 @ 0x0202dbf0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0202dbf0(int *p, int x, int y)
{
    int a;
    int b;
    a = *(volatile int *) &x;
    b = *(volatile int *) &y;
    p[0x36] = a;
    p[0x37] = b;
}
