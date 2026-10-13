/* func_ov113_0229a4a4 @ 0x0229a4a4, 0x60 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *self, int n);
extern void func_ov002_022080a0(void *self, int n);
extern void func_ov113_02299c44(void *self, int n);
extern int func_0206fe60(void);
extern void func_ov113_0229a108(void *self);
extern void func_ov002_02207fc0(void *self);
extern void func_ov002_02208098(void *self, int n);
extern void func_ov113_02299d84(void *self, int n);
extern void func_ov113_02299a44(void *self);
extern void func_ov002_02207e80(void *self, int a, int b, int c);

void func_ov113_0229a4a4(void *self)
{
    if (func_ov002_02207f48(self, 1) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov113_02299c44(self, 0);
        if (func_0206fe60() != 0) {
            func_ov113_0229a108(self);
        } else {
            func_ov002_02207fc0(self);
            func_ov002_02208098(self, 1);
            func_ov113_02299d84(self, 0x100);
            func_ov113_02299a44(self);
        }
    }
    func_ov002_02207e80(self, 2, 0, 0);
}
