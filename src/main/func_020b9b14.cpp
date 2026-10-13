/* func_020b9b14 @ 0x020b9b14, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b9b14 {
    char pad_00;
};

class UnkStruct_020b9b14_2 {
  public:
    virtual void vf0();
    virtual void vf1();

    char pad_04[8];         // offsets 0x04-0x0b
    unsigned char unk_0C;   // 0x0c
    unsigned char unk_0D;   // 0x0d
    unsigned char unk_0E;   // 0x0e
    unsigned char unk_0F;   // 0x0f
    UnkStruct_020b9b14 sub; // 0x10
};

extern "C" void func_020b9c68(UnkStruct_020b9b14_2 *self, int a, int b, int c);
extern "C" void func_020ba064(UnkStruct_020b9b14 *sub, int a, int b, int c, unsigned char d);
extern "C" unsigned char func_020ba03c(UnkStruct_020b9b14 *sub);
extern "C" int func_020b98c4(UnkStruct_020b9b14_2 *self);

extern "C" int func_020b9b14(UnkStruct_020b9b14_2 *self, int a, int b, int c, unsigned char d)
{
    func_020b9c68(self, a, b, c);
    self->unk_0E = 7;
    func_020ba064(&self->sub, a, b, c, d);
    self->unk_0F = func_020ba03c(&self->sub);
    self->unk_0C = 4;
    if (func_020b98c4(self) != 0) {
        return 1;
    }
    self->vf1();
    return 0;
}
