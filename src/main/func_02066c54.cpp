/* func_02066c54 @ 0x02066c54, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void func_02068d38(void *);
void func_0206899c(void *);
void func_02036480(void *);
void RtcSendPxiCommand(int);
extern const short data_020def28[];
extern char *data_021c526c;
}

class UnkStruct_02066c54_2 {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual void f23();
    virtual void f24();
    virtual void f25();
    virtual void f26();
    virtual void f27();
    virtual void f28();
};

struct UnkStruct_02066c54 {
    char pad_00[0xc];
    volatile int unk_0C;
    char pad_10[0x14 - 0x10];
    int unk_14;
    char pad_18[0x1c - 0x18];
    char unk_1C;
    char pad_1D[0x9c - 0x1d];
    int unk_9C;
    char pad_A0[0x14a8 - 0xa0];
    UnkStruct_02066c54_2 *unk_14A8;
    char pad_14AC[0x1a2c - 0x14ac];
    char unk_1A2C;
    char pad_1A2D[0x1e98 - 0x1a2d];
    unsigned char unk_1E98;
    char pad_1E99[1];
    unsigned char unk_1E9A;
};

extern "C" void func_02066c54(struct UnkStruct_02066c54 *self)
{
    func_02068d38((char *) self + 0x1c);
    self->unk_0C = 4;
    self->unk_9C = data_020def28[self->unk_0C];
    if (self->unk_1E98 == 0) {
        func_0206899c((char *) self + 0x1a2c);
        if (self->unk_14 != 1 && self->unk_14 != 2 && self->unk_14 != 3) {
            func_02036480(data_021c526c + 0x1c4);
        }
    }
    if (self->unk_1E9A == 0) {
        RtcSendPxiCommand(10);
    }
    self->unk_14A8->f28();
}
