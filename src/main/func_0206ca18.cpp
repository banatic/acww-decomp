/* func_0206ca18 @ 0x0206ca18, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206ca18 {
    char pad_00[0x2c];
    char *unk_2C;
} UnkStruct_0206ca18;

class VirtualObj {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
    virtual int getValue();
};

extern "C" VirtualObj *func_02068010(char *p);
extern "C" void func_020a9334(UnkStruct_0206ca18 *self, int value);
extern "C" void func_020a7994(char *p, int value);

extern "C" void func_0206ca18(UnkStruct_0206ca18 *self)
{
    VirtualObj *q;
    int v;

    q = func_02068010(self->unk_2C);
    v = q->getValue();
    func_020a9334(self, v);

    q = func_02068010(self->unk_2C);
    v = q->getValue();
    func_020a7994(self->unk_2C + 0x1a58, v);

    *(int *) (self->unk_2C + 0x1a60) = 1;
}
