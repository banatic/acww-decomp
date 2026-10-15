/* func_ov106_0229ec8c @ 0x0229ec8c, 0x5c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int n);
extern void func_020027f0(int n);
extern void func_ov106_0229c344(void *p, int n);
extern int func_ov106_0229c364(void *p, int n);
extern void func_ov002_02208090(void *p, int n);
extern void func_ov106_0229ec0c(void *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov106_0229eafc(void *p);

void func_ov106_0229ec8c(void *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(6);
        func_ov106_0229c344(self, 2);
        if (func_ov106_0229c364(self, 0x100) != 0) {
            func_ov002_02208090(self, 7);
            func_ov106_0229ec0c(self);
        } else {
            func_ov106_0229c344(self, 1);
            func_ov002_022080a0((void *) (self), 5);
        }
    } else {
        func_ov106_0229eafc(self);
    }
}
