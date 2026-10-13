/* func_020a9fac @ 0x020a9fac, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int a, int b);
extern void func_020ac39c(void *a, int b, int c);
extern void func_020abdc8(void *a);
extern int func_020aad3c(void *a);
extern void func_020abd68(void *a, int b, int c);
extern void func_020aae38(void *a);
extern void func_020a9fa4(void *a);

typedef struct UnkStruct_020a9fac {
    unsigned char pad_00[0xc];
    unsigned char pad_0C[0x148];
    unsigned char pad_154[0x38];
    int unk_18C;
    int unk_190;
    int unk_194;
} UnkStruct_020a9fac;

void func_020a9fac(UnkStruct_020a9fac *self)
{
    unsigned int flag;

    if (self->unk_194 > func_0209d368(100, 3) + 2) {
        self->unk_18C += func_0209d368(100, 6) - 6;
        self->unk_190 += func_0209d368(100, 7) + 6;
    } else {
        self->unk_18C += func_0209d368(100, 8) + 2;
        self->unk_190 += func_0209d368(100, 9) - 2;
    }

    self->unk_194 -= 1;
    flag = (self->unk_194 <= 0) ? 1 : 0;

    if (flag > 0) {
        self->unk_18C = 0;
        self->unk_190 = 0;
    }

    func_020ac39c((char *) self + 0xc, self->unk_18C, self->unk_190 + 4);

    if (flag > 0) {
        int result;

        func_020abdc8((char *) self + 0xc);
        result = func_020aad3c((char *) self + 0x154);
        func_020abd68((char *) self + 0xc, (result == 0) ? 1 : 0, 0);
        func_020aae38((char *) self + 0x154);
        func_020a9fa4(self);
    }
}
