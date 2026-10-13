/* func_ov131_0229b1f0 @ 0x0229b1f0, 0x5c bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *self);
extern int func_ov130_0229a080(void *self);
extern void func_ov002_02208098(void *self, int arg);
extern int func_ov130_0229a070(void *self);
extern int func_ov131_0229b07c(void *self);
extern void func_ov131_0229aee4(void *self);
extern void func_ov131_0229b04c(void *self);

void func_ov131_0229b1f0(void *self)
{
    if (func_0208e484((char *) self + 0x94) != 0) {
        if (func_ov130_0229a080((char *) self + 0x2c4) != 0) {
            func_ov002_02208098(self, 6);
        } else {
            if (func_ov130_0229a070((char *) self + 0x2c4) != 0) {
                if (func_ov131_0229b07c(self) != 0) {
                    return;
                }
                func_ov002_02208098(self, 2);
                func_ov131_0229aee4(self);
            } else {
                func_ov131_0229b04c(self);
            }
        }
    }
}
