/* talk_tags_25: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206ba08 @ 0x0206ba08, 0x5c bytes, Thumb
 * func_0206b984 @ 0x0206b984, 0x84 bytes, Thumb
 */

class UnkStruct_0206ba08 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int vfunc();
};

extern "C" void func_020a9334(void *self, int result);
extern "C" void func_0206ba64(void *self, UnkStruct_0206ba08 *obj, int flag);
extern "C" void func_020a7994(void *ptr, int result);

struct UnkStruct_0206ba08_2 {
    char pad_00[0x24];
    char *unk_24;
};

class UnkStruct_0206b984 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct SomeObj {
    char pad_00[0x24];
    char *base; // offset 0x24
    char pad_28[0x34];
    int unk_5C; // offset 0x5c
};

extern "C" int func_020a82f8(int);

extern "C" void func_0206ba08(UnkStruct_0206ba08_2 *self, int idx)
{
    UnkStruct_0206ba08 *obj = (UnkStruct_0206ba08 *) ((char *) self->unk_24 + 0x14b8 + 0x5c * idx);
    int res1 = obj->vfunc();
    func_020a9334(self, res1);
    func_0206ba64(self, obj, 1);
    int res2 = obj->vfunc();
    func_020a7994((char *) self->unk_24 + 0x1a58, res2);
    *(int *) ((char *) self->unk_24 + 0x1a60) = 1;
}

extern "C" void func_0206b984(SomeObj *obj, int idx)
{
    UnkStruct_0206b984 *p = (UnkStruct_0206b984 *) ((char *) obj->base + 0x18ac + idx * 0x5c);
    int val = *(int *) ((char *) obj->base + idx * 4 + 0x1a1c);

    func_020a9334((void *) obj, func_020a82f8(obj->unk_5C));
    func_020a9334((void *) obj, p->m3());
    func_020a9334((void *) obj, func_020a82f8(val));
    func_0206ba64((void *) obj, (UnkStruct_0206ba08 *) p, 0);
    func_020a7994((char *) obj->base + 0x1a58, p->m3());
    *(int *) ((char *) obj->base + 0x1a60) = 1;
}
