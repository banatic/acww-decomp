/* func_ov108_0229d904 @ 0x0229d904, 0x1c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov108_0229d8bc(void *p);

class UnkStruct_0229d904 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual int m3();
};

struct UnkStruct_0229d904_2 {
    char pad_00[0x2498];
    UnkStruct_0229d904 sub;
};

extern "C" int func_ov108_0229d904(UnkStruct_0229d904_2 *self)
{
    func_ov108_0229d8bc(self);
    return self->sub.m3();
}
