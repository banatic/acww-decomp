/* func_ov134_0229bcac @ 0x0229bcac, 0x44 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov134_0229b6b4(void *);
extern "C" void func_020b9ccc(void *);
extern "C" void func_ov134_0229a8a8(void *);

struct UnkStruct_0229bcac {
    char pad_00[0x804];
    int unk_804;
    char pad_808[0x20];
    int unk_828;
    char pad_82C[0x20];
    int unk_84C;
};

class UnkStruct_0229bcac_2 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" void func_ov134_0229bcac(UnkStruct_0229bcac *self)
{
    UnkStruct_0229bcac_2 *sub;
    func_ov134_0229b6b4(self);
    func_020b9ccc(&self->unk_804);
    func_020b9ccc(&self->unk_828);
    func_020b9ccc(&self->unk_84C);
    func_ov134_0229a8a8(self);
    sub = (UnkStruct_0229bcac_2 *) ((char *) self + 0x18);
    sub->v3();
}
