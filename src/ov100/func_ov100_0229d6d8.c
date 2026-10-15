/* func_ov100_0229d6d8 @ 0x0229d6d8, 0x44 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d620(int unused0, unsigned int unused1);
extern int func_ov100_0229d67c(void);
extern int func_ov100_0229d630(int unused0, unsigned int unused1);
extern int func_ov100_0229d648(int);
extern void func_ov100_0229d71c(int, int, int);

void func_ov100_0229d6d8(int a, int b, int c)
{
    int value_r4 = 0x20;
    int value_r6 = b;
    int value_r5 = a;

    if (c >= 0x6c) {
        if (func_ov100_0229d620(a, b)) {
            // clang-format off
            asm {
                mov r0, value_r5
            }
            // clang-format on
            value_r4 = func_ov100_0229d67c();
        }
    } else {
        if (func_ov100_0229d630(a, b)) {
            value_r4 = func_ov100_0229d648(value_r5);
        }
    }

    if (value_r4 != 0x20) {
        value_r6 = value_r4;
    }

    func_ov100_0229d71c(value_r5, value_r6, 4);
}
