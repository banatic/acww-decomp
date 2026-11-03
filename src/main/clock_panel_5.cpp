/* clock_panel_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208d5ec @ 0x0208d5ec, 0x64 bytes, Thumb
 * func_0208d594 @ 0x0208d594, 0x58 bytes, Thumb
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

extern "C" int func_020b45d0(UnkStruct_0208d5ec *, unsigned char, int, int, int, int);
extern "C" void func_02051648(MyPtrStruct *);
extern "C" void func_02051694(MyPtrStruct *);

typedef struct UnkStruct_0208d594_2 {
    char pad_00[0x10];
    int unk_10;
} UnkStruct_0208d594_2;

class FieldBC {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int method();
};

typedef struct UnkStruct_0208d594 {
    char pad_00[0x3C];
    UnkStruct_0208d594_2 *unk_3C;
    char pad_40[0x4D - 0x40];
    unsigned char unk_4D;
    char pad_4E[0x62 - 0x4E];
    unsigned char unk_62;
    char pad_63[0xBC - 0x63];
    FieldBC unk_BC;
} UnkStruct_0208d594;

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

extern "C" void func_0208d594(UnkStruct_0208d594 *p)
{
    if (p->unk_3C && p->unk_4D) {
        p->unk_4D = 0;
        func_020b45d0((UnkStruct_0208d5ec *) (&p->unk_BC), p->unk_62, 2, 6, 0, 1);
        UnkStruct_0208d594_2 *inner = p->unk_3C;
        inner->unk_10 = p->unk_BC.method();
        func_02051648((MyPtrStruct *) p->unk_3C);
        func_02051694((MyPtrStruct *) p->unk_3C);
    }
}
