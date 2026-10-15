/* func_020b5350 @ 0x020b5350, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020b5350_2 {
  public:
    virtual int vf0();
    virtual int vf1();
    virtual int vf2();
};

struct UnkStruct_020b5350 {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x3c - 0x28];
    int unk_3C;
    int unk_40;
    char pad_44;
    unsigned char unk_45;
    unsigned char unk_46;
    unsigned char unk_47;
    unsigned char unk_48;
};

extern "C" void func_020a94a4(struct UnkStruct_020b5350 *);
extern "C" void func_020a9354(struct UnkStruct_020b5350 *, int);
extern "C" int func_020a92d8(struct UnkStruct_020b5350 *, int);
extern "C" int func_020b4d0c(struct UnkStruct_020b5350 *);
extern "C" int func_020b4cd8(struct UnkStruct_020b5350 *);

extern "C" unsigned char func_020b5350(struct UnkStruct_020b5350 *self, unsigned char a1, unsigned char a2)
{
    self->unk_45 = 1;
    self->unk_40 = 0;
    self->unk_46 = a1;
    self->unk_47 = a2;
    self->unk_48 = 0;
    self->unk_3C = 0;

    func_020a94a4(self);

    UnkStruct_020b5350_2 *obj = (UnkStruct_020b5350_2 *) ((char *) self->unk_24 + 0x4c);
    int ret = obj->vf2();

    func_020a9354(self, ret);
    func_020a92d8(self, 0);

    if (self->unk_45 && self->unk_47) {
        if (func_020b4d0c(self) == 0 || func_020b4cd8(self) == 0) {
            self->unk_45 = 0;
        }
    }

    return self->unk_45;
}
