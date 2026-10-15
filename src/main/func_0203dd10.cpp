/* func_0203dd10 @ 0x0203dd10, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203dd10 {
    virtual void v0();
    virtual void v1();
    virtual int v2();
};

struct UnkStruct_0203dd10_2 {
    char pad_00[0x5c];
    UnkStruct_0203dd10 sub;
};

struct MainObj {
    char pad_00[0x24];
    UnkStruct_0203dd10_2 *inner;
    char pad_28[0x40 - (0x24 + 4)];
    int unk_40;
    unsigned char unk_44;
    char pad_45[0x50 - (0x44 + 1)];
    unsigned char unk_50;
    char pad_51[0x54 - (0x50 + 1)];
    int unk_54;
    int unk_58;
};

extern "C" void func_020a94a4(MainObj *self);
extern "C" void func_020a9354(MainObj *self, int ret);
extern "C" int func_020a92d8(MainObj *self, int arg);

extern "C" unsigned char func_0203dd10(MainObj *self, unsigned char param1)
{
    self->unk_44 = 1;
    self->unk_40 = 0;
    self->unk_50 = param1;
    self->unk_54 = 0;
    self->unk_58 = 0;
    func_020a94a4(self);
    int ret = self->inner->sub.v2();
    func_020a9354(self, ret);
    func_020a92d8(self, 0);
    return self->unk_44;
}
