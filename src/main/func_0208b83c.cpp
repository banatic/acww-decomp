/* func_0208b83c @ 0x0208b83c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0208b83c_2 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

typedef struct UnkStruct_0208b83c {
    unsigned char pad_00[0x10];
    int unk_10;
    unsigned char pad_14[0x28 - 0x14];
    void *unk_28;
    int unk_2C;
    unsigned char pad_30[0x38 - 0x30];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[0x50 - 0x3a];
    int unk_50;
    unsigned char pad_54[0x55 - 0x54];
    unsigned char unk_55;
} UnkStruct_0208b83c;

typedef struct UnkStruct_0208b83c_3 {
    unsigned char pad_00[0x38];
    UnkStruct_0208b83c *unk_38;
    UnkStruct_0208b83c_2 unk_3C;
} UnkStruct_0208b83c_3;

extern "C" UnkStruct_0208b83c *func_020a9034(int, int, int);
extern "C" int data_021c81d4;
extern "C" void func_02051624(UnkStruct_0208b83c *);
extern "C" void func_02051694(UnkStruct_0208b83c *);

extern "C" void func_0208b83c(UnkStruct_0208b83c_3 *self)
{
    UnkStruct_0208b83c *t;
    UnkStruct_0208b83c *d;
    UnkStruct_0208b83c_2 *s;
    volatile int pad;
    (void) &pad;
    if (self->unk_38 == 0) {
        self->unk_38 = func_020a9034(0x80, 8, 1);
        t = self->unk_38;
        if (t != 0) {
            t->unk_2C = 4;
            self->unk_38->unk_50 = 2;
            self->unk_38->unk_55 = 1;
            self->unk_38->unk_39 = 0;
            self->unk_38->unk_38 = 0xc;
            d = self->unk_38;
            s = &self->unk_3C;
            d->unk_10 = s->f3();
            self->unk_38->unk_28 = &data_021c81d4;
            func_02051624(self->unk_38);
            func_02051694(self->unk_38);
        }
    }
}
