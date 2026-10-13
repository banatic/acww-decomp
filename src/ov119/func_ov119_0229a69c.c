/* func_ov119_0229a69c @ 0x0229a69c, 0x78 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9c];
    unsigned char unk_9C;
    unsigned char unk_9D;
    unsigned char pad_9E[0xe0c - 0x9e];
    unsigned char sub_a[0x160c - 0xe0c];
    unsigned char sub_b[0x1e0c - 0x160c];
    void *unk_1E0C;
} UnkStruct_0229a69c;

extern void func_ov119_0229bacc(void *self, int kind);
extern void func_ov119_0229a410(void *self, int val);
extern void func_ov119_0229a714(void *self);

void func_ov119_0229a69c(UnkStruct_0229a69c *self, unsigned char val)
{
    if (val == self->unk_9C) {
        return;
    }
    self->unk_9D = val;
    self->unk_9C = val;
    if (self->unk_9C == 5) {
        func_ov119_0229bacc(self, 0xeb);
        self->unk_1E0C = self->sub_a;
    } else if (self->unk_9C == 4) {
        func_ov119_0229bacc(self, 0xea);
        self->unk_1E0C = self->sub_b;
    } else {
        func_ov119_0229bacc(self, 0xcd);
        self->unk_1E0C = self->sub_a;
    }
    func_ov119_0229a410(self, 2);
    func_ov119_0229a714(self);
}
