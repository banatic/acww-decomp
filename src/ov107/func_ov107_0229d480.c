/* func_ov107_0229d480 @ 0x0229d480, 0x20 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov107_0229d4d4(int);
extern void func_ov107_0229d4a0(int);

void func_ov107_0229d480(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov107_0229d4d4(r4);
    } else {
        func_ov107_0229d4a0(r4);
    }
}
