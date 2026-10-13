/* func_0206a0cc @ 0x0206a0cc, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206a0cc {
    unsigned char pad_00[0x24];
    unsigned char *unk_24;
    unsigned char pad_28[0x34];
    int unk_5C;
} UnkStruct_0206a0cc;

extern "C" {
extern int func_02067964(const void *p);
extern void func_0206bb9c(UnkStruct_0206a0cc *self, int a, const void *b);
extern int func_020a82f8(int value);
extern void func_020a9334(UnkStruct_0206a0cc *self, int value);
extern void func_020a7994(void *addr, int value);
extern unsigned char data_020df198[];
}

class UnkStruct_0206a0cc_2 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

extern "C" void func_0206a0cc(UnkStruct_0206a0cc *self)
{
    if (func_02067964(self->unk_24) == 0) {
        func_0206bb9c(self, 0xce0, data_020df198);
    }
    func_020a9334(self, func_020a82f8(self->unk_5C));
    func_020a9334(self, ((UnkStruct_0206a0cc_2 *) (self->unk_24 + 0x1cec))->m3());
    func_020a9334(self, func_020a82f8(6));
    func_020a7994(self->unk_24 + 0x1a58, ((UnkStruct_0206a0cc_2 *) (self->unk_24 + 0x1cec))->m3());
    *(int *) (self->unk_24 + 0x1a60) = 0;
}
