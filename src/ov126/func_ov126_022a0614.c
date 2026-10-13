/* func_ov126_022a0614 @ 0x022a0614, 0x6c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

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

extern int func_ov126_022a0740(struct UnkStruct_022a0614 *self);
extern void func_02051bf8(void *dst, int size);
extern void func_02051c08(void *dst, void *src, int size);
extern void func_ov126_0229f7b8(struct UnkStruct_022a0614 *self, int arg);
extern void func_ov095_022999f4(void *addr);
extern void func_ov126_022a0978(struct UnkStruct_022a0614 *self);

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
        func_ov126_0229f7b8(self, 8);
        func_ov095_022999f4(&self->unk_19C);
        func_ov126_022a0978(self);
    }
}
