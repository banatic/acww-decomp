/* func_ov120_0229b244 @ 0x0229b244, 0x6a bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c1c(void *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_ov002_02209018(void *, int);
extern int func_ov002_02208ff8(void *, unsigned);
extern int func_ov002_02208fac(void *, unsigned);
extern int func_0207094c(void *, unsigned);

void func_ov120_0229b244(int arg1, void *arg2, unsigned arg3)
{
    int t;
    if (arg3 == 0) {
        func_020a8c1c(arg2);
    } else if (arg3 == 1) {
        t = func_02099870((int) func_020984e8());
        func_ov002_02209018(arg2, t);
    } else if (arg3 >= 2 && arg3 < 6) {
        func_ov002_02208ff8(arg2, arg3 - 2);
    } else if (arg3 >= 6 && arg3 < 14) {
        func_ov002_02208fac(arg2, arg3 - 6);
    } else if (arg3 >= 14 && arg3 < 19) {
        func_0207094c(arg2, arg3 + 0x88);
    } else {
        func_020a8c1c(arg2);
    }
}
