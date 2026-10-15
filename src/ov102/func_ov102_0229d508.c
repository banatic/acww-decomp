/* func_ov102_0229d508 @ 0x0229d508, 0x44 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d454(int arg0, unsigned int arg1);
extern int func_ov102_0229d464(int arg0, unsigned int arg1);
extern int func_ov102_0229d4ac(void);
extern int func_ov102_0229d47c(int);
extern void func_ov102_0229d54c(int, int, int);

void func_ov102_0229d508(int p1, int p2, int p3)
{
    int x = 0x25;
    if (p3 >= 108) {
        if (func_ov102_0229d454(p1, p2)) {
            asm {
                mov r0, p1
            }
            x = func_ov102_0229d4ac();
        }
    } else {
        if (func_ov102_0229d464(p1, p2)) {
            x = func_ov102_0229d47c(p1);
        }
    }
    if (x != 0x25) {
        p2 = x;
    }
    func_ov102_0229d54c(p1, p2, 4);
}
