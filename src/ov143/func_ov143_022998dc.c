/* func_ov143_022998dc @ 0x022998dc, 0x48 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov143_022997d8(int);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);
extern int data_ov143_0229b178[];

void func_ov143_022998dc(int a, int b, int c, int d)
{
    int t = d - 2 * func_ov143_022997d8(a);
    func_02088df8(1, data_ov143_0229b178[b], c, t, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
