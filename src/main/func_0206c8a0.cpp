/* func_0206c8a0 @ 0x0206c8a0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern int func_02067964(void *);
extern void func_020a9334(void *, int);
extern void func_020a7994(void *, int);
}

class VirtualClass {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct SelfType {
    char pad_00[0x2c];
    char *ptr;
};

extern "C" void func_0206c8a0(SelfType *self)
{
    func_02067964(self->ptr);
    int res1 = ((VirtualClass *) (self->ptr + 0x1cec))->m3();
    func_020a9334(self, res1);
    int res2 = ((VirtualClass *) (self->ptr + 0x1cec))->m3();
    func_020a7994(self->ptr + 0x1a58, res2);
    *(int *) (self->ptr + 0x1a60) = 0;
}
