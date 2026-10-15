/* func_02069e98 @ 0x02069e98, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020677d0(void *);
extern "C" void func_0206bb9c(void *object, int code, const void *message);
extern "C" void func_020a9334(void *, int);
extern "C" void func_020a7994(void *, int);

class Obj3 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

typedef struct UnkStruct_02069e98 {
    char pad_00[0x24];
    char *unk_24;
} UnkStruct_02069e98;

extern unsigned char data_020df170[];

extern "C" void func_02069e98(UnkStruct_02069e98 *self)
{
    if (func_020677d0(self->unk_24) == 0) {
        func_0206bb9c(self, 0x0d9f, &data_020df170);
    }
    int r = reinterpret_cast<Obj3 *>(self->unk_24 + 0x1da8)->f3();
    func_020a9334(self, r);
    r = reinterpret_cast<Obj3 *>(self->unk_24 + 0x1da8)->f3();
    func_020a7994((void *) (self->unk_24 + 0x1a58), r);
    *(int *) (self->unk_24 + 0x1a60) = 1;
}
