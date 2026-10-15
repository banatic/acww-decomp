/* func_ov094_0229ae10 @ 0x0229ae10, 0x44 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a524(int a, int b);
extern int func_02088d9c(int x);
extern int func_02088d94(int x);

int func_ov094_0229ae10(int a0, int a1, int a2, int a3)
{
    int base1;
    int high1;
    int low2;
    int high2;
    int v;
    int c1;
    int c2;

    base1 = a1;
    high1 = base1 - 0x7c;
    low2 = a2 - 0x74;
    high2 = a2 - 0x5c;
    v = func_ov094_0229a524(a0, a3);
    c1 = func_02088d9c(v);
    if (base1 - 0x94 < c1 && c1 < high1) {
        c2 = func_02088d94(v);
        if (low2 < c2 && c2 < high2) {
            return 1;
        }
    }
    return 0;
}
