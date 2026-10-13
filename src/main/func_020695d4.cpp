/* func_020695d4 @ 0x020695d4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *);

struct VTableClass {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void target();
};

struct UnkStruct_020695d4 {
    unsigned char pad_00[0x14a8];
    VTableClass *vtable_obj;
};

struct UnkStruct_020695d4_2 {
    unsigned char pad_00[0x24];
    UnkStruct_020695d4 *inner;
    unsigned char pad_28[0x10];
    unsigned char unk_38;
};

extern "C" void func_020695d4(UnkStruct_020695d4_2 *obj)
{
    VTableClass *v = obj->inner->vtable_obj;
    func_020a8750(&obj->unk_38);
    v->target();
}
