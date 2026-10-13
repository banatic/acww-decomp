/* func_ov106_0229eb48 @ 0x0229eb48, 0x58 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *ptr, int flag);
extern void func_020027f0(int arg);
extern void func_ov106_0229c344(void *self, int arg);
extern int func_ov106_0229c364(void *self, int arg);
extern void func_ov002_022080a0(void *self, int arg);
extern void func_ov106_0229eeb4(void *self);
extern void func_ov106_0229eb28(void *self);

void func_ov106_0229eb48(void *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov106_0229c344(self, 0x80);
        if (func_ov106_0229c364(self, 0x8000) != 0) {
            func_ov002_022080a0(self, 5);
            func_ov106_0229c344(self, 1);
        } else {
            func_ov106_0229eeb4(self);
        }
    } else {
        func_ov106_0229eb28(self);
    }
}
