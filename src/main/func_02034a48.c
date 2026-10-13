/* func_02034a48 @ 0x02034a48, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034b80(int p1, int p2, int p3, int p4);
extern int func_02034b04(int p1, int p2, int p3, int p4);

int func_02034a48(int a1, int a2, int a3, int a4, unsigned char a5)
{
    if (a3) {
        return func_02034b80(a1, a2, a4, a5);
    } else {
        return func_02034b04(a1, a2, a4, a5);
    }
}
