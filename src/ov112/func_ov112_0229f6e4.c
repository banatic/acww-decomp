/* func_ov112_0229f6e4 @ 0x0229f6e4, 0x4c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov112_0229fe60(void *, unsigned int);
extern void func_ov112_0229f6d4(void *, unsigned char);
extern void func_ov112_0229f8e4(void *);
extern void func_ov095_0229cd30(void *);
extern void func_ov112_0229f488(void *);
extern void func_ov095_0229b3ec(void *);

typedef struct {
    char pad_00[0x98];
    unsigned int unk_98;
    unsigned int unk_9C;
    char pad_A0[0x20];
    unsigned char unk_C0;
    char pad_C1[0x2c3];
    char sub_384;
} UnkStruct_0229f6e4;

void func_ov112_0229f6e4(UnkStruct_0229f6e4 *self)
{
    func_ov112_0229fe60(self, 0x40);
    self->unk_98 = 0x30;
    self->unk_9C = 0x38;
    func_ov112_0229f6d4(self, self->unk_C0);
    func_ov112_0229f8e4(self);
    func_ov095_0229cd30(&self->sub_384);
    func_ov112_0229f488(self);
    func_ov095_0229b3ec(&self->sub_384);
}
