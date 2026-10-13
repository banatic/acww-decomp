/* func_ov134_0229aed4 @ 0x0229aed4, 0x2c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229af00(int);
extern int func_ov134_0229ae9c(int, int, int);

int func_ov134_0229aed4(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r3;
    int result;

    if (r1 == 0x38 && r2 == 0x34) {
        result = 0;
    } else {
        result = func_ov134_0229ae9c(r5, func_ov134_0229af00(r5), r4);
    }

    return result;
}
