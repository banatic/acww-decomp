/* func_020b4ea0 @ 0x020b4ea0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

class UnkStruct_020b4ea0 {
  public:
    virtual int f0() = 0;
    virtual int f1() = 0;
    virtual int f2() = 0;
    virtual int f3() = 0;
};

struct UnkStruct_020b4ea0_2 {
    char pad_00[0x24];
    unsigned char *unk_24;
    char pad_28[0x3c - 0x28];
    unsigned int unk_3C;
    char pad_40[0x44 - 0x40];
    unsigned char unk_44;
    unsigned char unk_45;
    char pad_46[0x47 - 0x46];
    unsigned char unk_47;
    unsigned char unk_48;
};

extern "C" int func_020a7c74(int, int);
extern "C" int func_02050bdc_unk(int);
extern "C" int func_020b4d70(int);
extern "C" void func_020b512c(void *);

extern "C" void func_020b4ea0(UnkStruct_020b4ea0_2 *self)
{
    if (self->unk_47) {
        int r4, r6;
        UnkStruct_020b4ea0 *obj = *(UnkStruct_020b4ea0 **) ((char *) self->unk_24 + 0x18f0);
        r4 = obj->f3();
        r6 = func_020a7c74(r4, 0);
        r4 = func_020a7c74(r4, 1);
        if (self->unk_48) {
            r6 = func_02050bdc_unk(r6);
            self->unk_48 = 0;
        }
        if (self->unk_48) {
            r4 = func_02050bdc_unk(r4);
            self->unk_48 = 0;
        }
        if (func_020b4d70(r6) && func_020b4d70(r4)) {
            self->unk_3C = r4;
            func_020b512c(self);
            self->unk_3C = r6;
            func_020b512c(self);
            self->unk_44 = 1;
        } else {
            self->unk_45 = 0;
        }
    }
}
