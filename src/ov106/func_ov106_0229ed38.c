/* func_ov106_0229ed38 @ 0x0229ed38, 0x60 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *, int);
extern void func_ov106_0229cc50(void *);
extern int func_ov106_0229c364(void *, int);
extern void *func_020ee45c(void *);
extern void func_ov092_02299324(void *, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov002_02208090(void *, int);

void func_ov106_0229ed38(void *self)
{
    func_ov002_02207d24((char *) self + 0x21b8, 1);
    func_ov106_0229cc50(self);
    if (func_ov106_0229c364(self, 0x100) == 0) {
        func_ov092_02299324(func_020ee45c(self), 0x44, 1);
    }
    func_ov002_02207f04(self, 2, 0, 2, 0x30);
    func_ov002_02207e90(self, 0xc0);
    func_ov002_02208090(self, 5);
}
