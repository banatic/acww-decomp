/* func_ov096_022a1554 @ 0x022a1554, 0x80 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *self, int arg);
extern void func_020027f0(int arg);
extern void func_ov096_0229c2dc(void *self, int arg);
extern int func_020ee45c(void *self);
extern int func_ov096_0229c2fc(void *self, int arg);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov090_022990d0(int arg);
extern void func_ov096_022a18a0(void *self);
extern void func_ov002_02207e80(void *self, int arg1, int arg2, int arg3);

void func_ov096_022a1554(void *self)
{
    int r4;
    if (func_ov002_02207f3c(self, 0)) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov096_0229c2dc(self, 0x100);
        r4 = func_020ee45c(self);
        if (func_ov096_0229c2fc(self, 0x20000)) {
            func_ov002_022080a0((void *) (self), 5);
            func_ov096_0229c2dc(self, 1);
        } else {
            func_ov090_022990d0(r4);
            func_ov096_022a18a0(self);
        }
    } else {
        func_ov002_02207e80(self, 3, 0, 0);
        func_ov002_02207e80(self, 4, 0, 0);
    }
}
