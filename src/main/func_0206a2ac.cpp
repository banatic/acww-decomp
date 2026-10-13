/* func_0206a2ac @ 0x0206a2ac, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class VirtualClass {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

typedef struct UnkStruct_0206a2ac {
    char pad_00[0x24];
    char *unk_24;
} UnkStruct_0206a2ac;

extern "C" {
VirtualClass *func_02068010(void *arg);
void func_020a9334(UnkStruct_0206a2ac *self, int value);
void func_020a7994(char *dest, int value);
void func_0206a2ac(UnkStruct_0206a2ac *self)
{
    VirtualClass *obj = func_02068010(self->unk_24);
    func_020a9334(self, obj->v3());
    obj = func_02068010(self->unk_24);
    func_020a7994(self->unk_24 + 0x1a58, obj->v3());
    *(int *) (self->unk_24 + 0x1a60) = 1;
}
}
