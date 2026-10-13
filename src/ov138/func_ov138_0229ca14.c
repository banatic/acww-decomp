/* func_ov138_0229ca14 @ 0x0229ca14, 0x3c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229a24c(char *);
extern int func_ov134_0229a8a0(char *);
extern void func_ov138_0229c9c0(char *);

void func_ov138_0229ca14(char *self)
{
    int v;
    if (func_ov134_0229a24c(self + 0x2c8) == 0) {
        return;
    }
    v = func_ov134_0229a8a0(self + 0x2c8);
    if (v == 6) {
        self[0x95] = 3;
    } else {
        self[0x95] = (char) v;
    }
    func_ov138_0229c9c0(self);
}
