/* func_02069bd0 @ 0x02069bd0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02069bd0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(int a, int b);
};

struct UnkStruct_02069bd0_2 {
    unsigned char pad_00[0x14a8];
    UnkStruct_02069bd0 *obj;
};

struct UnkStruct_02069bd0_3 {
    unsigned char pad_00[0x24];
    UnkStruct_02069bd0_2 *inner;
    unsigned char pad_28[0x10];
};

extern "C" void func_020a8718(char *dst, char *a, char *b);
extern "C" int func_020644cc(int x);
extern "C" void func_0206b964(UnkStruct_02069bd0_3 *self, char *c);

extern "C" void func_02069bd0(UnkStruct_02069bd0_3 *self)
{
    unsigned char local[8];
    self->inner->obj->v13(0, 2);
    func_020a8718((char *) self + 0x38, (char *) &local[1], (char *) &local[2]);
    local[0] = ((unsigned char *) &local[1])[func_020644cc(2)];
    func_0206b964(self, (char *) local);
}
