/* func_0206a3cc @ 0x0206a3cc, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206a3cc {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int VFunc();
};

struct UnkStruct_0206a3cc_2 {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x5c - 0x28];
    int unk_5C;
};

extern "C" void func_02067a3c(char *p);
extern "C" int func_020a82f8(int arg);
extern "C" void func_020a9334(UnkStruct_0206a3cc_2 *obj, int value);
extern "C" void func_020a7994(char *p, int value);

extern "C" void func_0206a3cc(UnkStruct_0206a3cc_2 *obj)
{
    func_02067a3c(obj->unk_24);
    func_020a9334(obj, func_020a82f8(obj->unk_5C));
    func_020a9334(obj, ((UnkStruct_0206a3cc *) (obj->unk_24 + 0x1c8c))->VFunc());
    func_020a9334(obj, func_020a82f8(8));
    func_020a7994(obj->unk_24 + 0x1a58, ((UnkStruct_0206a3cc *) (obj->unk_24 + 0x1c8c))->VFunc());
    *((int *) (obj->unk_24 + 0x1a60)) = 0;
}
