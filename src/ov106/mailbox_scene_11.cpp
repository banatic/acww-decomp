/* mailbox_scene_11: 2 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229f2fc @ 0x0229f2fc, 0xe4 bytes, Thumb
 * func_ov106_0229f208 @ 0x0229f208, 0xf4 bytes, Thumb
 */

class UnkStruct_0229f2fc {
  public:
    virtual void f0();
    virtual void f1();
    virtual int f2();
};

extern "C" int func_ov106_0229c364(void *self, int kind);
extern "C" void func_ov106_0229ce64(void *self);
extern "C" int func_0206fe54(void);
extern "C" void func_ov002_02209eb8(void *p);
extern "C" void func_ov002_0220ad18(void *a, void *b);
extern "C" void func_ov094_0229a850(void *a, int b, int c);
extern "C" void func_ov094_0229b738(void *a, int b, int c);
extern "C" void func_ov094_02299d84(void *receiver, int value);
extern "C" void func_ov094_0229b6c8(void *a, void *b, int c);
extern "C" int func_ov002_02207f60(void *self);
extern "C" void func_0208f210(void *a, int b, int c);

class UnkStruct_0229f208 {
  public:
    unsigned char pad_00[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229f208::*PMF)();

extern PMF data_ov106_0229f678;
extern PMF data_ov106_0229f6d0;
extern PMF data_ov106_0229f6c8;
extern PMF data_ov106_0229f6c0;
extern PMF data_ov106_0229f6b8;
extern PMF data_ov106_0229f6b0;
extern PMF data_ov106_0229f6a8;
extern PMF data_ov106_0229f6a0;
extern PMF data_ov106_0229f698;
extern PMF data_ov106_0229f690;
extern PMF data_ov106_0229f688;
extern "C" void func_ov106_0229e960(UnkStruct_0229f208 *self);
extern "C" void func_ov106_0229e928(UnkStruct_0229f208 *self);

extern "C" int func_ov106_0229f2fc(void *self)
{
    if (func_ov106_0229c364(self, 1) == 0) {
        return 1;
    }

    UnkStruct_0229f2fc *obj1 = (UnkStruct_0229f2fc *) ((char *) self + 0x21b8);
    if (((void) (obj1->f2()), func_0206fe54()) != 0) {
        func_ov002_02209eb8((char *) self + 0x22a0);
    }

    func_ov106_0229ce64(self);

    if (func_ov106_0229c364(self, 2) != 0) {
        func_ov002_0220ad18((char *) self + 0x3fb4, *(void **) ((char *) self + 0xa0));
        int r4 = *(int *) ((char *) self + 0x98) - 0x10;
        func_ov094_0229a850((char *) self + 0xf8, 0, r4);
        func_ov094_0229b738((char *) self + 0xb58, 0, r4);
        func_ov094_02299d84((char *) self + 0xb80, r4);
    }

    if (func_ov106_0229c364(self, 0x200) != 0) {
        func_ov094_0229b6c8((char *) self + 0xb58, *(void **) ((char *) self + 0x9c), ~0xF);
    }

    if (func_ov106_0229c364(self, 0x80) != 0) {
        int r2 = func_ov002_02207f60(self);
        func_0208f210((char *) self + 0x2b3c, 0, r2);
        ((UnkStruct_0229f2fc *) ((volatile char *) self + 0x2b3c))->f2();
    }

    return 1;
}

extern "C" int func_ov106_0229f208(UnkStruct_0229f208 *self)
{
    static PMF table[11] = {data_ov106_0229f678, data_ov106_0229f6d0, data_ov106_0229f6c8, data_ov106_0229f6c0,
                            data_ov106_0229f6b8, data_ov106_0229f6b0, data_ov106_0229f6a8, data_ov106_0229f6a0,
                            data_ov106_0229f698, data_ov106_0229f690, data_ov106_0229f688};

    func_ov106_0229e960(self);
    (self->*table[self->idx])();
    func_ov106_0229e928(self);
    return 1;
}
