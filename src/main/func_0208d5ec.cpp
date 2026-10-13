/* func_0208d5ec @ 0x0208d5ec, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0208d5ec {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

struct MyPtrStruct {
    char pad_00[0x10];
    int unk_10;
};

struct SomeSelf {
    char pad_00[0x38];
    MyPtrStruct *ptr;
    char pad_3C[0x10];
    unsigned char flag;
    char pad_4D[0x16];
    unsigned char val;
    char pad_64[0x3c];
    UnkStruct_0208d5ec obj;
};

extern "C" void func_020b45d0(UnkStruct_0208d5ec *, unsigned char, int, int, int, int);
extern "C" void func_02051648(MyPtrStruct *);
extern "C" void func_02051694(MyPtrStruct *);

extern "C" void func_0208d5ec(SomeSelf *self)
{
    if (self->ptr) {
        if (self->flag) {
            self->flag = 0;
            unsigned char v = self->val;
            if (v >= 12) {
                v = (unsigned char) (v - 12);
            }
            func_020b45d0(&self->obj, v, 2, 6, 0, 1);
            MyPtrStruct *p = self->ptr;
            int *field = &p->unk_10;
            *field = self->obj.f3();
            func_02051648(self->ptr);
            func_02051694(self->ptr);
        }
    }
}
