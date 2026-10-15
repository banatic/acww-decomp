/* func_ov142_0229bc9c @ 0x0229bc9c, 0x60 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_02299668(void *self, int a);
extern void func_ov142_02299658(void *self, int a);
extern void func_ov142_0229ac58(void *self, int a, int b, int c, int d, int e);
extern void func_ov142_0229abfc(void *object);
extern int func_ov002_02207f48(void *self, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov142_0229b214(void *self);
extern void func_ov142_0229bb08(void *self);

void func_ov142_0229bc9c(void *self)
{
    if (func_ov142_02299668(self, 1) == 0) {
        func_ov142_02299658(self, 1);
        func_ov142_0229ac58(self, 0xb8, 0x16d, 4, 0xf, 0);
        func_ov142_0229abfc(self);
    }
    if (func_ov002_02207f48(self, 0) != 0) {
        func_ov002_022080a0((void *) (self), 2);
        func_ov142_0229b214(self);
    }
    func_ov142_0229bb08(self);
}
