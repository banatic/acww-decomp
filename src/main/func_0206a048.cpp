/* func_0206a048 @ 0x0206a048, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {

struct UnkStruct_0206a048 {
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct UnkStruct_0206a048_2 {
    char pad_00[0x1a58];
    int array[2];
    int unk_1A60;
    char pad1[0x1d0c - 0x1a64];
    UnkStruct_0206a048 sub;
};

struct UnkStruct_0206a048_3 {
    char pad_00[0x24];
    UnkStruct_0206a048_2 *base;
    char pad1[0x5c - 0x28];
    int unk_5C;
};

int func_020678f8(UnkStruct_0206a048_2 *);
void func_0206bb9c(void);
int func_020a82f8(int);
void func_020a9334(UnkStruct_0206a048_3 *, int);
void func_020a7994(int *, int);
extern int data_020df188;

void func_0206a048(UnkStruct_0206a048_3 *self)
{
    if (func_020678f8(self->base) == 0) {
        asm {
            mov r0, self
            ldr r1, =0xcf5
            ldr r2, =data_020df188
            bl func_0206bb9c
        }
    }
    func_020a9334(self, func_020a82f8(self->unk_5C));
    func_020a9334(self, self->base->sub.m3());
    func_020a9334(self, func_020a82f8(6));
    int r = self->base->sub.m3();
    func_020a7994(self->base->array, r);
    self->base->unk_1A60 = 0;
}
}
