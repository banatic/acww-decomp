/* func_ov133_0229b714 @ 0x0229b714, 0x28 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099658(void);
extern int func_0206fc8c(void);
extern int func_02077d00(int);

int func_ov133_0229b714(void)
{
    int r5;
    int r4;
    int r0;

    func_020984e8();
    r5 = func_02099658();
    r4 = func_0206fc8c();
    r0 = func_02077d00(r5);
    r0 += r4 * 0x24;
    return r0;
}
