/* func_ov115_0229e0e8 @ 0x0229e0e8, 0x56 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *arg);
extern int func_ov114_0229c60c(void *p);
extern int func_ov115_0229e4cc(void *self, int type);
extern int func_ov114_0229c2c8(void *p);
extern void func_ov002_02208098(void *p, int val);
extern void func_ov115_0229ddd0(void *p);

void func_ov115_0229e0e8(void *self)
{
    int result;

    if (func_0208e484((char *) self + 0x94) == 0) {
        return;
    }
    result = func_ov114_0229c60c((char *) self + 0xf8);
    if (result != -1) {
        if (func_ov115_0229e4cc(self, result) != 0) {
            return;
        }
    } else {
        if (func_ov114_0229c2c8((char *) self + 0xf8) != 0) {
            func_ov002_02208098(self, 6);
            return;
        }
    }
    func_ov002_02208098(self, 2);
    func_ov115_0229ddd0(self);
}
