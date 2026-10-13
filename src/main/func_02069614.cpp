/* func_02069614 @ 0x02069614, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *p);

class UnkStruct_02069614_3 {
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
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
};

struct UnkStruct_02069614 {
    char pad_00[0x14a8];
    UnkStruct_02069614_3 *obj;
};

struct UnkStruct_02069614_2 {
    char pad_00[0x24];
    UnkStruct_02069614 *u;
    char pad_28[0x38 - 0x28];
    char sub[1];
};

extern "C" void func_02069614(struct UnkStruct_02069614_2 *self)
{
    UnkStruct_02069614_3 *obj = self->u->obj;
    func_020a8750(&self->sub[0]);
    obj->v16();
}
