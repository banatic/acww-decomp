/* func_0206d484 @ 0x0206d484, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a9334(void *self, int val);
extern "C" void func_0206d4e0(void *self, void *obj);
extern "C" void func_020a7994(unsigned char *addr, int val);

class UnkStruct_0206d484 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

typedef struct {
    unsigned char pad_00[0x2c];
    unsigned char *base;
} UnkStruct_0206d484_2;

extern "C" void func_0206d484(UnkStruct_0206d484_2 *self, int index)
{
    UnkStruct_0206d484 *o = (UnkStruct_0206d484 *) (self->base + 0x14b8 + index * 0x5c);
    func_020a9334(self, o->m3());
    func_0206d4e0(self, o);
    func_020a7994(self->base + 0x1a58, o->m3());
    *(unsigned int *) (self->base + 0x1a60) = 0;
}
