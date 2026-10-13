/* func_ov103_0229d158 @ 0x0229d158, 0x38 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(void *ptr);
extern void func_ov103_0229c8e8(void *self, unsigned char byte);
extern void func_ov103_0229cfa0(void *self);
extern void func_ov103_0229c964(void *self);

void func_ov103_0229d158(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x225c)) {
        func_ov103_0229c8e8(self, *((unsigned char *) self + 0x2da3));
        func_ov103_0229cfa0(self);
    } else {
        func_ov103_0229c964(self);
    }
}
