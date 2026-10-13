/* func_020345e0 @ 0x020345e0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034448(int, int, int, int);

int func_020345e0(int a, int *b, int c)
{
    int d;
    int e;
    d = b[0] >> 13;
    e = b[2] >> 13;
    func_02034448(a, d, e, c);
    return a;
}
