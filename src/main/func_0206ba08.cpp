/* func_0206ba08 @ 0x0206ba08, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
