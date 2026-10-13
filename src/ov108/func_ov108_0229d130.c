/* func_ov108_0229d130 @ 0x0229d130, 0x38 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(unsigned char *ptr);
extern int func_ov108_0229c8a4(unsigned char *self, unsigned char byte);
extern int func_ov108_0229cf4c(unsigned char *self);
extern int func_ov108_0229c918(unsigned char *self);

int func_ov108_0229d130(unsigned char *self)
{
    if (func_ov002_02209d8c(self + 0x2480)) {
        func_ov108_0229c8a4(self, self[0x2af]);
        return func_ov108_0229cf4c(self);
    } else {
        return func_ov108_0229c918(self);
    }
}
