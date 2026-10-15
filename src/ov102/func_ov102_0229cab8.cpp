/* func_ov102_0229cab8 @ 0x0229cab8, 0x98 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229cab8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" int func_ov102_0229c2a8(unsigned char *self, int v);
extern "C" void func_ov102_0229c288(unsigned char *self, int v);
extern "C" int func_ov102_0229cb84(unsigned char *self);
extern "C" int func_ov102_0229cb74(unsigned char *self);
extern "C" void func_ov002_0220a0b4(UnkStruct_0229cab8 *obj, int a, int b);
extern "C" void func_ov002_0220a05c(UnkStruct_0229cab8 *obj, int a, int b, int c, int d);
extern "C" unsigned char *func_ov002_02208098(unsigned char *self, unsigned char value);

extern "C" void func_ov102_0229cab8(unsigned char *self)
{
    int a, b;

    if (func_ov102_0229c2a8(self, 8) != 0) {
        a = func_ov102_0229cb84(self);
        b = func_ov102_0229cb74(self);
        func_ov002_0220a0b4((UnkStruct_0229cab8 *) (self + 0x2274), a, b);
        func_ov102_0229c288(self, 8);
    } else {
        a = func_ov102_0229cb84(self);
        b = func_ov102_0229cb74(self);
        func_ov002_0220a05c((UnkStruct_0229cab8 *) (self + 0x2274), a, b, 3, 1);
        self[0x25A7] = self[0x8D];
        func_ov002_02208098(self, 5);
        if (func_ov102_0229c2a8(self, 0x100) != 0) {
            ((UnkStruct_0229cab8 *) (self + 0x2274))->v3();
            func_ov102_0229c288(self, 0x100);
        }
    }
}
