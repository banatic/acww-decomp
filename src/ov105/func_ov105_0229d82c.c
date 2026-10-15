/* func_ov105_0229d82c @ 0x0229d82c, 0x44 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d75c(int, unsigned int arg1);
extern int func_ov105_0229d7d4(void);
extern int func_ov105_0229d76c(int, unsigned int arg1);
extern int func_ov105_0229d78c(int);
extern void func_ov105_0229d870(int, int, int);

void func_ov105_0229d82c(int a, int b, int c)
{
    int x = 0x40;
    if (c >= 0xc0) {
        if (func_ov105_0229d75c(a, b) != 0) {
            asm {
                mov r0, a
            }
            x = func_ov105_0229d7d4();
        }
    } else {
        if (func_ov105_0229d76c(a, b) != 0) {
            x = func_ov105_0229d78c(a);
        }
    }
    if (x != 0x40) {
        b = x;
    }
    func_ov105_0229d870(a, b, 4);
}
