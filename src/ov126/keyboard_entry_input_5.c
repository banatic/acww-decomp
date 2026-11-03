/* keyboard_entry_input_5: 3 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a06b4 @ 0x022a06b4, 0x24 bytes, Thumb
 * func_ov126_022a0680 @ 0x022a0680, 0x34 bytes, Thumb
 * func_ov126_022a0614 @ 0x022a0614, 0x6c bytes, Thumb
 */

typedef struct UnkStruct_022a06b4 {
    char pad_00[0xa8];
    unsigned char unk_A8;
    unsigned char unk_A9;
    unsigned char unk_AA;
} UnkStruct_022a06b4;

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned char a8;
    unsigned char a9;
    unsigned char aa;
} UnkStruct_022a0680;

struct UnkStruct_022a0614 {
    unsigned char pad_00[0xa9];
    unsigned char a;
    unsigned char b;
    unsigned char pad_AB[0xf1];
    unsigned char unk_19C[1];
    unsigned char pad_19D[0x40ab];
    unsigned short arr4248[16];
    unsigned char arr4268[16];
};

extern void func_ov126_0229f7a8(UnkStruct_022a06b4 *self, int a);
extern void func_ov126_0229f7b8(UnkStruct_022a0680 *s, int n);
extern int func_ov126_022a0740(struct UnkStruct_022a0614 *self);
extern void func_02051bf8(void *dst, int size);
extern void func_02051c08(void *dst, void *src, int size);
extern void func_ov095_022999f4(void *addr);
extern void func_ov126_022a0978(struct UnkStruct_022a0614 *self);

void func_ov126_022a06b4(UnkStruct_022a06b4 *self)
{
    self->unk_A9 = self->unk_A8;
    self->unk_AA = self->unk_A8;
    func_ov126_0229f7a8(self, 4);
}

void func_ov126_022a0680(UnkStruct_022a0680 *s)
{
    s->aa = s->a8;
    if (s->aa != s->a9) {
        func_ov126_0229f7b8(s, 4);
    } else {
        func_ov126_0229f7a8((UnkStruct_022a06b4 *) s, 4);
    }
}

void func_ov126_022a0614(struct UnkStruct_022a0614 *self)
{
    if (func_ov126_022a0740(self) != 0) {
        unsigned char b = self->b;
        unsigned char a = self->a;
        int min, diff;
        if (a > b) {
            min = b;
            diff = a - b;
        } else {
            min = a;
            diff = b - a;
        }
        func_02051bf8(self->arr4268, 0x10);
        func_02051c08(&self->arr4248[min], self->arr4268, diff);
        func_ov126_0229f7b8((UnkStruct_022a0680 *) self, 8);
        func_ov095_022999f4(&self->unk_19C);
        func_ov126_022a0978(self);
    }
}
