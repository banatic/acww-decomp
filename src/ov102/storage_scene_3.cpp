/* storage_scene_3: 3 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229cb50 @ 0x0229cb50, 0x24 bytes, Thumb
 * func_ov102_0229cab8 @ 0x0229cab8, 0x98 bytes, Thumb
 * func_ov102_0229ca98 @ 0x0229ca98, 0x20 bytes, Thumb
 */

extern "C" void func_ov002_0220a374(void *, int);

class UnkStruct_0229cb50 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_0229cb50_2 {
    char pad_00[0x2274];
    UnkStruct_0229cb50 sub;
};

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

class UnkStruct_0229ca98_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

extern "C" void func_ov002_0220a0ec(UnkStruct_0229ca98_2 *obj);

struct UnkStruct_0229ca98 {
    char pad_00[0x2274];
    UnkStruct_0229ca98_2 member;
};

extern "C" void func_ov102_0229cb50(UnkStruct_0229cb50_2 *self)
{
    func_ov002_0220a374(&self->sub, 0);
    self->sub.v3();
}

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

extern "C" void func_ov102_0229ca98(UnkStruct_0229ca98 *self)
{
    func_ov002_0220a0ec(&self->member);
    self->member.f3();
}
