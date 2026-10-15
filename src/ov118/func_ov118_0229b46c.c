/* func_ov118_0229b46c @ 0x0229b46c, 0x6a bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c1c(int);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_ov002_02209018(int, int);
extern int func_ov002_02208ff8(int, int);
extern int func_ov002_02208fac(int, int);
extern int func_0207094c(int, int);

void func_ov118_0229b46c(int a, int b, unsigned int c)
{
    if (c == 0) {
        func_020a8c1c(b);
    } else if (c == 1) {
        func_ov002_02209018(b, func_02099870(func_020984e8()));
    } else if (c >= 2 && c < 6) {
        func_ov002_02208ff8(b, c - 2);
    } else if (c >= 6 && c < 14) {
        func_ov002_02208fac(b, c - 6);
    } else if (c >= 14 && c < 19) {
        func_0207094c(b, c + 0x88);
    } else {
        func_020a8c1c(b);
    }
}
