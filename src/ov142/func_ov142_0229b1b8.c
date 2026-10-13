/* func_ov142_0229b1b8 @ 0x0229b1b8, 0x20 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov142_0229b1fc(int);
extern void func_ov142_0229b1d8(int);

void func_ov142_0229b1b8(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov142_0229b1fc(r4);
    } else {
        func_ov142_0229b1d8(r4);
    }
}
