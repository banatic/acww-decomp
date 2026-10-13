/* func_0206b984 @ 0x0206b984, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
extern "C" void func_020a9334(SomeObj *, int);
extern "C" void func_0206ba64(SomeObj *, UnkStruct_0206b984 *, int);
extern "C" void func_020a7994(void *, int);

extern "C" void func_0206b984(SomeObj *obj, int idx)
{
    UnkStruct_0206b984 *p = (UnkStruct_0206b984 *) ((char *) obj->base + 0x18ac + idx * 0x5c);
    int val = *(int *) ((char *) obj->base + idx * 4 + 0x1a1c);

    func_020a9334(obj, func_020a82f8(obj->unk_5C));
    func_020a9334(obj, p->m3());
    func_020a9334(obj, func_020a82f8(val));
    func_0206ba64(obj, p, 0);
    func_020a7994((char *) obj->base + 0x1a58, p->m3());
    *(int *) ((char *) obj->base + 0x1a60) = 1;
}
