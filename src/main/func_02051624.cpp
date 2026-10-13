/* func_02051624 @ 0x02051624, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02051624 {
  public:
    virtual unsigned int f0();
    virtual unsigned int f1();
    virtual unsigned int f2();
    virtual unsigned int f3();
    unsigned char pad_04[0x1c];
    unsigned int unk_20;
    unsigned char pad_24[0xc];
    unsigned int unk_30;
};

extern "C" void func_02051624(UnkStruct_02051624 *self)
{
    unsigned int res = self->f3();
    unsigned int tmp = self->unk_20 << 3;
    if (tmp > res) {
        self->unk_30 = tmp - res;
    } else {
        self->unk_30 = 0;
    }
}
