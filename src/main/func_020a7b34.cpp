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

extern void (UnkStruct_020a7b34::*data_0213dd98)();
extern void (UnkStruct_020a7b34::*data_020e3cf4)();
extern void (UnkStruct_020a7b34::*data_020e3d04)();
extern void (UnkStruct_020a7b34::*data_020e3ce4)();

extern "C" void func_020a7b34(UnkStruct_020a7b34 *self, unsigned int arg)
{
    self->unk_3C = arg;
    static void (UnkStruct_020a7b34::*table[5])() = {data_0213dd98, data_020e3cf4, data_0213dd98, data_020e3d04,
                                                     data_020e3ce4};
    void (UnkStruct_020a7b34::*pmf)() = table[self->unk_24];
    if (pmf) {
        (self->*pmf)();
    }
}
