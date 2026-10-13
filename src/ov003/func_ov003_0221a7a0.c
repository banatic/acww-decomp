/* func_ov003_0221a7a0 @ 0x0221a7a0, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221a8c4(void *self);
extern void func_ov003_0221a35c(void *self, int a);
extern int func_ov003_0221a860(void *self);
extern int func_020b0594(int a, int b, int *c, int *d, int *e, int f, int g, int h);

typedef struct {
    char pad_00[8];
    unsigned int unk_08;
    char pad_0C[0x60 - 0xc];
    int unk_60;
    char pad_64[0x26c - 0x64];
    int unk_26C;
    char pad_270[0x378 - 0x270];
    unsigned short a : 2;
    unsigned short b : 2;
    unsigned short c : 12;
} UnkStruct_0221a7a0;

extern unsigned char data_021f3b56[];

void func_ov003_0221a7a0(UnkStruct_0221a7a0 *self)
{
    int r;
    int v10, v14, v18;

    if (func_ov003_0221a8c4(self) != 0) {
        func_ov003_0221a35c(self, 0);
        return;
    }
    r = func_ov003_0221a860(self);
    self->a = (self->unk_08 - 2) >> 1;
    if (func_020b0594((unsigned int) data_021f3b56, self->a, &v10, &v14, &v18, 0, 0, 0) == 0) {
        return;
    }
    self->b = v18;
    if (r != 0) {
        self->unk_26C = v14;
        func_ov003_0221a35c(self, 9);
    } else {
        self->unk_26C = v10;
        self->unk_60 = v14 * 2 - (v14 >> 3) - (v10 >> 3) - 0x400;
        func_ov003_0221a35c(self, 0xb);
    }
}
