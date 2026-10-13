/* func_0207099c @ 0x0207099c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02051624(void *);
extern "C" void func_02051694(void *);

struct Target {
    char pad[0x10];
    int unk_10;
};

class UnkStruct_0207099c {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
    char pad[0x64];
    Target *p;
};

extern "C" void func_0207099c(UnkStruct_0207099c *self)
{
    Target *q;
    if ((q = self->p) != 0) {
        q->unk_10 = self->v3();
        func_02051624(self->p);
        func_02051694(self->p);
    }
}
