/* func_02070978 @ 0x02070978, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02070978 {
    unsigned char pad0[0x10];
    int unk_10;
    unsigned char pad_14[0x30 - 0x14];
    int unk_30;
};

class UnkStruct_02070978_2 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    unsigned char pad0[0x64];
    UnkStruct_02070978 *sub;
};

extern "C" void func_02051694(UnkStruct_02070978 *p);

extern "C" void func_02070978(UnkStruct_02070978_2 *self, int arg)
{
    UnkStruct_02070978 *p = self->sub;
    if (p == 0) {
        return;
    }
    p->unk_10 = self->v3();
    self->sub->unk_30 = arg;
    func_02051694(self->sub);
}
