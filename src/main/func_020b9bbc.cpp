/* func_020b9bbc @ 0x020b9bbc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020b9c68(void *);
extern "C" void func_020ba0c0(void *, int, int, int, int);
extern "C" unsigned char func_020ba0a4(void *);
extern "C" int func_020b98c4(void *);

class UnkStruct_020b9bbc {
  public:
    virtual void f0();
    virtual void f1();
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
};

extern "C" int func_020b9bbc(UnkStruct_020b9bbc *self, int a, int b, int c, int d)
{
    func_020b9c68(self);
    self->unk_0E = 5;
    func_020ba0c0((void *) ((char *) self + 0x10), a, b, c, d);
    self->unk_0F = func_020ba0a4((void *) ((char *) self + 0x10));
    self->unk_0C = 4;
    if (func_020b98c4(self) != 0) {
        return 1;
    }
    self->f1();
    return 0;
}
