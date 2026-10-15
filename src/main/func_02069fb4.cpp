/* func_02069fb4 @ 0x02069fb4, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_0206786c(void *p);
void func_0206bb9c(void);
int func_020a82f8(int arg);
void func_020a9334(void *self, int val);
void func_020a7994(void *addr, int val);
extern char data_020df178;
}

struct UnkStruct_02069fb4 {
    char pad_00[0x24];
    unsigned char *unk_24;
    char pad_28[0x34]; // from 0x28 to 0x5b
    int unk_5C;
};

class UnkStruct_02069fb4_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3();
};

extern "C" void func_02069fb4(UnkStruct_02069fb4 *self)
{
    if (func_0206786c(self->unk_24) == 0) {
        asm {
            mov r0, self
            ldr r1, =0xD0B
            ldr r2, =data_020df178
            bl func_0206bb9c
        }
    }
    func_020a9334(self, func_020a82f8(self->unk_5C));
    func_020a9334(self, reinterpret_cast<UnkStruct_02069fb4_2 *>(self->unk_24 + 0x1d2c)->f3());
    int val = 5;
    if (self->unk_24[0x1e76] != 0) {
        val = 6;
    }
    func_020a9334(self, func_020a82f8(val));
    func_020a7994(self->unk_24 + 0x1a58, reinterpret_cast<UnkStruct_02069fb4_2 *>(self->unk_24 + 0x1d2c)->f3());
    *((unsigned int *) (self->unk_24 + 0x1a60)) = 0;
}
