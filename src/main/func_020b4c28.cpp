/* func_020b4c28 @ 0x020b4c28, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020b4c28 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

struct Owner {
    char pad_00[0x28];
    UnkStruct_020b4c28 *unk_28;
    char pad_2C[4];
    int unk_30;
};

extern "C" void func_020b4c28(Owner *self, UnkStruct_020b4c28 *obj)
{
    self->unk_28 = obj;
    self->unk_30 = obj->v3();
}
