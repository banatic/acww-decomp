/* func_ov126_0229f9b8 @ 0x0229f9b8, 0x80 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0209871c(int, int);
extern int func_020988a4(int, int);
extern int func_02098844(int, int);
extern int func_020950a8(int);
extern int func_02051bb4(int, void *, int);
extern void func_0206fc4c(int);
extern void func_020950ac(int, void *);
extern char data_021dc7bc[];

void func_ov126_0229f9b8(void *param)
{
    int x = func_020984e8();
    int y;
    int z;
    int i;

    func_02099870(x);
    y = func_02099870(x);
    z = func_0209871c((int) data_021dc7bc, y);

    for (i = 0; i < 4; i++) {
        if (i == z) {
            continue;
        }
        if (func_020988a4((int) data_021dc7bc, i) == 0) {
            continue;
        }
        if (func_02051bb4(func_020950a8(func_02099870(func_02098844((int) data_021dc7bc, i))), (char *) param + 0x4248, 6) ==
            0) {
            continue;
        }
        func_0206fc4c(2);
        return;
    }
    func_020950ac(func_02099870(x), (char *) param + 0x4248);
}
