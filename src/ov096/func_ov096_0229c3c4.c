/* func_ov096_0229c3c4 @ 0x0229c3c4, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229c2fc(int, int);
extern void func_ov096_0229c2dc(int, int);
extern int func_0203ac5c(void);
extern int func_0203ac2c(void);
extern int func_0203ac44(void);

void func_ov096_0229c3c4(int param)
{
    if (func_ov096_0229c2fc(param, 0x800) == 0) {
        return;
    }

    if (func_0203ac5c()) {
        if (func_ov096_0229c2fc(param, 0x400) == 0) {
            func_0203ac2c();
        }
    } else {
        if (func_ov096_0229c2fc(param, 0x400) != 0) {
            func_0203ac44();
        }
    }

    func_ov096_0229c2dc(param, 0x800);
}
