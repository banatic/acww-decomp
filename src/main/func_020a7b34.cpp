/* func_020a7b34 @ 0x020a7b34, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a7b34 {
  public:
    virtual void vfunc();
    unsigned char pad_04[0x20];
    unsigned int unk_24;
    unsigned char pad_28[0x14];
    unsigned int unk_3C;
    void m0();
    void m1();
    void m2();
    void m3();
    void m4();
};

extern void (UnkStruct_020a7b34::*__ptmf_null)();
extern void (UnkStruct_020a7b34::*data_020e3cf4)();
extern void (UnkStruct_020a7b34::*data_020e3d04)();
extern void (UnkStruct_020a7b34::*data_020e3ce4)();

extern int data_021f43fc;
extern void (UnkStruct_020a7b34::*data_021f448c[5])();

extern "C" void func_020a7b34(UnkStruct_020a7b34 *self, unsigned int arg)
{
    self->unk_3C = arg;
    if (!(data_021f43fc & 1)) {
        data_021f448c[0] = __ptmf_null;
        data_021f448c[1] = data_020e3cf4;
        data_021f448c[2] = __ptmf_null;
        data_021f448c[3] = data_020e3d04;
        data_021f448c[4] = data_020e3ce4;
        data_021f43fc |= 1;
    }
    void (UnkStruct_020a7b34::*pmf)() = data_021f448c[self->unk_24];
    if (pmf) {
        (self->*pmf)();
    }
}
