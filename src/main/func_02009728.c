/* func_02009728 @ 0x02009728, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02009728 UnkStruct_02009728;
struct UnkStruct_02009728 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x234 - 0x9c];
    unsigned int unk_234;
    char pad_238[0x2d4 - 0x238];
    int unk_2D4;
    char pad_2D8[0x2e0 - 0x2d8];
    int unk_2E0;
    char pad_2E4[0x704 - 0x2e4];
    int unk_704;
};

extern void func_02010f5c(int);
extern int func_0200f290(UnkStruct_02009728 *p, int a);
extern int FX_MulFunc(int a, int b);
extern void func_020109c8(UnkStruct_02009728 *p, int a, int b, int c);
extern void func_02054860(unsigned int *p);
extern void func_0200f95c(UnkStruct_02009728 *p);

void func_02009728(UnkStruct_02009728 *self)
{
    int val;
    int result;

    if (self->unk_704 == 0) {
        func_02010f5c((int) self);
        return;
    }

    val = self->unk_98;
    if (func_0200f290(self, 0x18)) {
        val <<= 1;
    }

    result = FX_MulFunc(val, 0x3ae1);
    if (result <= self->unk_2D4) {
        self->unk_2E0 = result;
    }

    if (val > 0x53f) {
        if (self->unk_704 != 2) {
            func_020109c8(self, 2, 3, 0);
        }
    } else {
        if (self->unk_704 != 1) {
            func_020109c8(self, 1, 3, 0);
        }
    }

    func_02054860(&self->unk_234);
    func_0200f95c(self);
}
