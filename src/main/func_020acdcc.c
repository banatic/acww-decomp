/* func_020acdcc @ 0x020acdcc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int, int);
extern void func_020acc0c(int, int, int, int);

void func_020acdcc(int a0, int a1, int a2, int a3)
{
    int r6;

    if (a3 == 0) {
        a3 = 1;
    }
    r6 = 0x1000;
    if (a3 != 0x1f) {
        r6 = FX_Div((a3 - 1) << 12, 0x1e000);
    }
    func_020acc0c(a0, a1, a2, r6);
}
