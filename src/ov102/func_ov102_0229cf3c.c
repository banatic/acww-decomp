/* func_ov102_0229cf3c @ 0x0229cf3c, 0x36 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(void *self, void *other);
extern int func_ov102_0229d454(void *self, void *other);
extern int func_ov102_0229d400(void *self, void *other);
extern void func_ov094_0229aafc(void *self_plus, int value);

void func_ov102_0229cf3c(void *self, void *other)
{
    if (func_ov102_0229d464(self, other) != 0 || func_ov102_0229d454(self, other) != 0) {
        func_ov094_0229aafc((char *) self + 0xcc, func_ov102_0229d400(self, other));
    }
}
