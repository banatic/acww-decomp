/* func_02094cf8 @ 0x02094cf8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e29fc;
extern int data_021d5658;
extern void func_02091494(int, int, int, int, int, int, int);
extern int func_02090c2c(int, int, int, int);

int func_02094cf8(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int saved_a0 = a0;
    int saved_a1 = a1;
    int r4 = a5;
    int result;
    if (r4 == 0) {
        r4 = (int) &data_020e29fc;
    }
    result = 3;
    func_02091494((int) &data_021d5658, -1, saved_a1, a2, a3, a4, -1);
    if (func_02090c2c(saved_a0, a2, a3, r4) != 0) {
        result = 1;
    }
    return result;
}
