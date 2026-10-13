/* func_020b9c10 @ 0x020b9c10, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020b9c10 {
  public:
    virtual void func0();
    virtual void func1();
    char pad_04[8];
    unsigned char unk_0C;
    char pad_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
    struct UnkStruct_020b9c10_2 {
        int pad_00;
    } sub;
};

extern "C" void func_020b9c68(void *p);
extern "C" void func_020ba0f8(void *p, int a, int b, int c, int d, int e);
extern "C" int func_020ba0cc(void *p);
extern "C" int func_020b98c4(void *p);

extern "C" int func_020b9c10(UnkStruct_020b9c10 *self, int a, int b, int c, int d, int e)
{
    func_020b9c68(self);
    self->unk_0E = 4;
    func_020ba0f8(&self->sub, a, b, c, d, e);
    self->unk_0F = func_020ba0cc(&self->sub);
    self->unk_0C = 4;
    if (func_020b98c4(self)) {
        return 1;
    } else {
        self->func1();
        return 0;
    }
}
