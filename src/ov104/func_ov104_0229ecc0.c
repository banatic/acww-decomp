/* func_ov104_0229ecc0 @ 0x0229ecc0, 0x5c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_020027f0(int);
extern int func_ov104_0229c344(void *, int);
extern int func_ov104_0229c364(void *, int);
extern int func_ov104_0229ec4c(void *);
extern int func_ov104_0229eb68(void *);
extern int func_ov002_02207f3c(void *, int);
extern int func_ov002_02208090(void *, int);
extern int func_ov002_022080a0(void *, int);

void func_ov104_0229ecc0(void *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(6);
        func_ov104_0229c344(self, 2);
        if (func_ov104_0229c364(self, 0x100) != 0) {
            func_ov002_02208090(self, 7);
            func_ov104_0229ec4c(self);
        } else {
            func_ov104_0229c344(self, 1);
            func_ov002_022080a0(self, 5);
        }
    } else {
        func_ov104_0229eb68(self);
    }
}
