/* func_0206c8f0 @ 0x0206c8f0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class VirtualClass {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

typedef struct UnkStruct_0206c8f0 {
    char pad_00[0x2c];
    char *base;
} UnkStruct_0206c8f0;

extern "C" void func_020679b0(char *p);
extern "C" void func_020a9334(UnkStruct_0206c8f0 *p, int value);
extern "C" void func_020a7994(char *p, int value);
extern "C" void func_0206c8f0(UnkStruct_0206c8f0 *self)
{
    func_020679b0(self->base);
    int r1 = ((VirtualClass *) (self->base + 0x1ccc))->m3();
    func_020a9334(self, r1);
    int r2 = ((VirtualClass *) (self->base + 0x1ccc))->m3();
    func_020a7994(self->base + 0x1a58, r2);
    *(int *) (self->base + 0x1a60) = 0;
}
