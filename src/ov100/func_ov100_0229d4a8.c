/* func_ov100_0229d4a8 @ 0x0229d4a8, 0x4a bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(void);
extern int func_ov100_0229d620(int, int);
extern int func_ov100_0229d5d4(int, int);
extern void func_ov094_0229aa14(int, int, int, int);
extern void func_ov094_0229a9b4(int, int);

void func_ov100_0229d4a8(int r0, int r1, int r2, int r3)
{
    int r4 = r0;
    int r5 = r1;
    int r6 = r2;
    int r7 = r3;

    if (func_ov100_0229d630() == 0) {
        if (func_ov100_0229d620(r4, r5) == 0) {
            return;
        }
    }

    r5 = func_ov100_0229d5d4(r4, r5);
    func_ov094_0229aa14(r4 + 0xcc, r5, r6, r7);
    func_ov094_0229a9b4(r4 + 0xcc, r5);
}
