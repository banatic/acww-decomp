/* func_ov106_0229f2fc @ 0x0229f2fc, 0xe4 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
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
