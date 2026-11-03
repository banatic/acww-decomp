/* talk_tags_3: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069614 @ 0x02069614, 0x20 bytes, Thumb
 * func_020695f4 @ 0x020695f4, 0x20 bytes, Thumb
 * func_020695d4 @ 0x020695d4, 0x20 bytes, Thumb
 * func_020695b4 @ 0x020695b4, 0x20 bytes, Thumb
 * func_02069594 @ 0x02069594, 0x20 bytes, Thumb
 * func_02069574 @ 0x02069574, 0x20 bytes, Thumb
 * func_02069554 @ 0x02069554, 0x20 bytes, Thumb
 * func_02069534 @ 0x02069534, 0x20 bytes, Thumb
 * func_02069514 @ 0x02069514, 0x20 bytes, Thumb
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

class UnkStruct_020695f4 {
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
    virtual void v17();
};

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

struct UnkStruct_020695b4;

class Target {
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
    virtual void v17();
    virtual void v18();
    virtual void v19();
};

struct UnkClass {
    char pad_00[0x24];
    UnkStruct_020695b4 *unk_24;
    char pad_28[0x10];
    char unk_38;
};

struct UnkStruct_020695b4 {
    char pad_00[0x14a8];
    Target *unk_14A8;
};

struct UnkStruct_02069594 {
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
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void method();
};

struct UnkStruct_02069594_2 {
    char pad_00[0x14a8];
    UnkStruct_02069594 *unk_14A8;
};

struct UnkStruct_02069594_3 {
    char pad_00[0x24];
    UnkStruct_02069594_2 *unk_24;
    char pad_28[0x10];
    char unk_38;
};

class VtblClass {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
};

struct DataBlock {
    char pad_00[0x14a8];
    VtblClass *obj;
};

struct UnkStruct_02069574 {
    char pad_00[0x24];
    DataBlock *data;
    char pad_28[0x38 - 0x28];
    char sub;
};

struct UnkStruct_02069554 {
    virtual void *f0();
    virtual void *f1();
    virtual void *f2();
    virtual void *f3();
    virtual void *f4();
    virtual void *f5();
    virtual void *f6();
    virtual void *f7();
    virtual void *f8();
    virtual void *f9();
    virtual void *f10();
    virtual void *f11();
    virtual void *f12();
    virtual void *f13();
    virtual void *f14();
    virtual void *f15();
    virtual void *f16();
    virtual void *f17();
    virtual void *f18();
    virtual void *f19();
    virtual void *f20();
    virtual void *f21();
    virtual void *f22();
};

struct UnkStruct_02069554_2 {
    char pad_00[0x14a8];
    UnkStruct_02069554 *obj;
};

struct UnkStruct_02069554_3 {
    char pad_00[0x24];
    UnkStruct_02069554_2 *base;
    char pad_28[0x38 - 0x28];
    char unk_38;
};

class UnkStruct_02069534 {
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
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void called();
};

struct Param {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x10];
    int unk_38;
};

struct UnkStruct_02069514_2 {
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
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void method();
};

struct UnkStruct_02069514 {
    char pad_00[0x24];
    void **ptr;
    char pad_28[0x10];
};

extern "C" void func_02069614(struct UnkStruct_02069614_2 *self)
{
    UnkStruct_02069614_3 *obj = self->u->obj;
    func_020a8750(&self->sub[0]);
    obj->v16();
}

extern "C" void func_020695f4(char *self)
{
    char *p;
    UnkStruct_020695f4 *obj;
    p = *(char **) (self + 0x24);
    obj = *(UnkStruct_020695f4 **) (p + 0x14a8);
    func_020a8750(self + 0x38);
    obj->v17();
}

extern "C" void func_020695d4(UnkStruct_020695d4_2 *obj)
{
    VTableClass *v = obj->inner->vtable_obj;
    func_020a8750(&obj->unk_38);
    v->target();
}

extern "C" void func_020695b4(UnkClass *self)
{
    Target *target = self->unk_24->unk_14A8;
    func_020a8750(&self->unk_38);
    target->v19();
}

extern "C" void func_02069594(UnkStruct_02069594_3 *self)
{
    UnkStruct_02069594 *obj = self->unk_24->unk_14A8;
    func_020a8750(&self->unk_38);
    obj->method();
}

extern "C" void func_02069574(UnkStruct_02069574 *self)
{
    DataBlock *dp = self->data;
    VtblClass *v = dp->obj;
    func_020a8750(&self->sub);
    v->vf21();
}

extern "C" void *func_02069554(UnkStruct_02069554_3 *self)
{
    UnkStruct_02069554 *obj = self->base->obj;
    func_020a8750(&self->unk_38);
    return obj->f22();
}

extern "C" void func_02069534(Param *param)
{
    UnkStruct_02069534 *obj;
    obj = *(UnkStruct_02069534 **) ((char *) param->unk_24 + 0x14a8);
    func_020a8750((void *) &param->unk_38);
    obj->called();
}

extern "C" void func_02069514(UnkStruct_02069514 *s)
{
    UnkStruct_02069514_2 *obj = (UnkStruct_02069514_2 *) s->ptr[0x14a8 / 4];
    func_020a8750((char *) s + 0x38);
    obj->method();
}
