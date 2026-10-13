/* func_ov135_0229c858 @ 0x0229c858, 0x20 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov135_0229c8b4(int);
extern void func_ov135_0229c878(int);

void func_ov135_0229c858(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov135_0229c8b4(r4);
    } else {
        func_ov135_0229c878(r4);
    }
}
