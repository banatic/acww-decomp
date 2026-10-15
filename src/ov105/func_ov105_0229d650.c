/* func_ov105_0229d650 @ 0x0229d650, 0x4c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

int func_ov105_0229d650(int a, int b);

extern int func_ov105_0229d428(int, int);
extern int func_ov105_0229d59c(int, int);
extern int func_02066830(int, int);
extern void func_ov105_0229d5dc(int, unsigned char, int);
extern void func_ov105_0229d0d4(int, int);

int func_ov105_0229d650(int a, int b)
{
    if (func_ov105_0229d428(a, b) == 0) {
        int res = func_ov105_0229d59c(a, b);
        func_02066830(a + 0x1b4, res);
        func_ov105_0229d5dc(a, *(unsigned char *) (a + 0x2b7), a + 0x1b4);
    }
    func_ov105_0229d0d4(a, b);
    return 1;
}
