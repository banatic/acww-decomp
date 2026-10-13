/* func_ov102_0229d37c @ 0x0229d37c, 0x74 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229aee8(void *ptr);
extern int func_ov094_0229a69c(void *ptr, int value);
extern int func_ov094_0229aeb8(void *ptr, int a, int b);
extern int func_ov102_0229d3f0(void *self, int value);
extern int func_ov102_0229d274(void *self, int value);

int func_ov102_0229d37c(void *self, int arg1, int arg2, int flag)
{
    int result;
    result = func_ov094_0229aee8((char *) self + 0xcc);
    if (result != 0x23) {
        if (flag != 0) {
            if (func_ov094_0229a69c((char *) self + 0xcc, result) != 0) {
                return 0x25;
            }
        }
        return func_ov102_0229d3f0(self, result);
    } else {
        result = func_ov094_0229aeb8((char *) self + 0xcc, arg1, arg2);
        if (result != 0x23) {
            if (flag != 0) {
                if (func_ov094_0229a69c((char *) self + 0xcc, result) != 0) {
                    return 0x25;
                }
            }
            return func_ov102_0229d274(self, result);
        } else {
            return 0x25;
        }
    }
}
