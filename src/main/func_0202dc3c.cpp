/* func_0202dc3c @ 0x0202dc3c, 0x210 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

union UnkStruct_0202dc3c {
    double d;
    int i[2];
};
extern UnkStruct_0202dc3c __ptmf_null;

struct UnkStruct_0202dc3c_2 {
    unsigned char pad_00[0x18];
};
extern UnkStruct_0202dc3c_2 data_021c283c[];

extern unsigned char data_021c1e84[0x40];

struct UnkStruct_0202dc3c_3 {
    unsigned char pad_00[0x830];
    int unk_830;
};

class UnkStruct_0202dc3c_4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    unsigned char pad_04[0xc8 - 4];
    UnkStruct_0202dc3c unk_C8, unk_D0, unk_D8, unk_E0, unk_E8, unk_F0, unk_F8;
    UnkStruct_0202dc3c_3 *unk_100;
    unsigned char pad_104[0x124 - 0x104];
    unsigned short unk_124;
    int unk_128, unk_12C, unk_130, unk_134, unk_138;
    unsigned char unk_13C;
    unsigned char pad_13D[0x154 - 0x13d];
    int unk_154;
    unsigned char unk_158, unk_159;
    int unk_15C, unk_160, unk_164, unk_168;
    UnkStruct_0202dc3c unk_16C, unk_174, unk_17C, unk_184, unk_18C;
    unsigned char pad_194[0x19c - 0x194];
    unsigned short unk_19C;
    unsigned char unk_19E;
    int unk_1A0;
};

extern "C" void *func_020984e8(void);
extern "C" void *func_02099870(void *);
extern "C" void func_0202da88(UnkStruct_0202dc3c_4 *, UnkStruct_0202dc3c_2 *);
extern "C" int func_02080728(int, void *);
extern "C" int func_020807c0(int, int);
extern "C" void func_0201cf54(UnkStruct_0202dc3c_4 *);
extern "C" void MI_CpuFill8(void *, int, int);

extern "C" void func_0202dc3c(UnkStruct_0202dc3c_4 *self, void *arg1, unsigned int arg2)
{
    void *obj;
    UnkStruct_0202dc3c t;
    UnkStruct_0202dc3c t2;

    if (func_020984e8() != 0) {
        obj = func_02099870(func_020984e8());
    } else {
        obj = 0;
    }
    self->v2();
    self->unk_100 = (UnkStruct_0202dc3c_3 *) arg1;
    if (arg2 < 0x11) {
        func_0202da88(self, &data_021c283c[arg2]);
    }
    self->unk_C8 = __ptmf_null;
    self->unk_D0 = __ptmf_null;
    self->unk_D8 = t = __ptmf_null;
    self->unk_E0 = t;
    self->unk_E8 = t;
    self->unk_F0 = t;
    self->unk_F8 = t;
    self->unk_124 = 0xfff1;
    self->unk_138 = 0;
    self->unk_128 = -1;
    self->unk_12C = 0;
    self->unk_130 = -1;
    self->unk_134 = 0;
    if (obj != 0 && self->unk_100 != 0) {
        self->unk_128 = func_02080728(self->unk_100->unk_830, obj);
        self->unk_12C = func_020807c0(self->unk_100->unk_830, self->unk_128);
    }
    func_0201cf54(self);
    self->unk_154 = 0;
    self->unk_158 = 0;
    self->unk_159 = 0;
    self->unk_15C = 0;
    self->unk_160 = 0;
    self->unk_164 = 0;
    self->unk_168 = 0;
    self->unk_16C = t2 = __ptmf_null;
    self->unk_174 = t2;
    self->unk_17C = t2;
    self->unk_184 = t2;
    self->unk_18C = t2;
    self->unk_19C = 0xfff1;
    self->unk_19E = 0;
    self->unk_1A0 = 0;
    MI_CpuFill8(data_021c1e84, 0, 0x40);
    self->unk_13C = 0;
}
