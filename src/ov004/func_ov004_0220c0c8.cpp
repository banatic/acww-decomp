/* func_ov004_0220c0c8 @ 0x0220c0c8, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int data_ov004_0224fbf0[2];
extern int data_ov004_0224fc00[2];
extern int data_ov004_0224fc18[2];
}

class UnkStruct_0220c0c8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0x130];
    int unk_134;
};

extern "C" void func_ov004_0220c0c8(UnkStruct_0220c0c8 *self)
{
    static void (UnkStruct_0220c0c8::*mtbl[3])() = {*reinterpret_cast<void (UnkStruct_0220c0c8::**)()>(data_ov004_0224fbf0),
                                                    *reinterpret_cast<void (UnkStruct_0220c0c8::**)()>(data_ov004_0224fc00),
                                                    *reinterpret_cast<void (UnkStruct_0220c0c8::**)()>(data_ov004_0224fc18)};
    int idx = self->unk_134;
    if (idx < 3) {
        (self->*(mtbl[idx]))();
    }
}
