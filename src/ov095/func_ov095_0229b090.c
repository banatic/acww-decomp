/* func_ov095_0229b090 @ 0x0229b090, 0x48 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_020896b8(int, int, int, int, int, int, int);
extern int data_ov095_0229e380;
extern int data_ov095_0229e390;

void func_ov095_0229b090(int p0, int p1, int p2, int p3, int p4)
{
    func_020896b8(1, (int) &data_ov095_0229e380, p1, p2 + p4, p3, 2, 0);
    func_020896b8(1, (int) &data_ov095_0229e390, p1, p2, -1, 2, 0);
}
