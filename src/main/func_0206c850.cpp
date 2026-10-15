/* func_0206c850 @ 0x0206c850, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206c850 {
    char pad_00[0x2c];
    char *base;
};

class UnkStruct_0206c850_2 {
  public:
    virtual int vf0();
    virtual int vf1();
    virtual int vf2();
    virtual int vf3(); // vtable offset 0xc
};

extern "C" int func_020678f8(char *);
extern "C" void func_020a9334(struct UnkStruct_0206c850 *, int);
extern "C" void func_020a7994(char *, int);

extern "C" void func_0206c850(struct UnkStruct_0206c850 *self)
{
    func_020678f8(self->base);
    int ret1 = ((UnkStruct_0206c850_2 *) (self->base + 0x1d0c))->vf3();
    func_020a9334(self, ret1);
    int ret2 = ((UnkStruct_0206c850_2 *) (self->base + 0x1d0c))->vf3();
    func_020a7994(self->base + 0x1a58, ret2);
    *(int *) (self->base + 0x1a60) = 0;
}
