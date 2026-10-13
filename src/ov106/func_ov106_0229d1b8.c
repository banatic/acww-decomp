/* func_ov106_0229d1b8 @ 0x0229d1b8, 0x54 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(int);
extern int func_020984e8(void);
extern int func_02066648(int);
extern int func_0204bd20(int, int);
extern int func_020996ac(int);
extern void OSi_DoUnlockByWord__main_0203cd2c(int, void *, int, int);

void func_ov106_0229d1b8(int a, int b)
{
    if (func_02065ec0(b) == 2 || func_02065ec0(b) == 3) {
        int x = func_020984e8();
        unsigned short s = 0xfff1;
        s = (unsigned short) func_0204bd20(func_02066648(b), 4);
        OSi_DoUnlockByWord__main_0203cd2c(func_020996ac(x), &s, 0, 1);
    }
}
