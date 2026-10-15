/* func_ov128_0229bff0 @ 0x0229bff0, 0x154 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];
extern int func_ov002_02208014(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a0b4(void *addr, int a, int b);
extern void func_ov127_02299b58(void *addr, int val);
extern int func_ov127_02299abc(void *addr, int val, int zero);
extern void func_ov128_0229be44(void *self);
extern void func_ov128_0229bc10(void *self);
extern void func_ov128_0229b7cc(void *self, int val);
extern void func_ov128_0229bc88(void *self);
extern void func_ov128_0229bb20(void *self);
typedef struct UnkStruct_0229bff0 {
    unsigned char pad_00[0x110];
    void *unk_110;
    unsigned char pad_114[0x4a4 - 0x114];
    void *unk_4A4;
    unsigned char pad_4A8[0x2d48 - 0x4a8];
    int unk_2D48;
    int unk_2D4C;
} UnkStruct_0229bff0;
void func_ov128_0229bff0(UnkStruct_0229bff0 *self)
{
    if (func_ov002_02208014()) {
        func_ov128_0229be44(self);
        return;
    }
    {
        unsigned short flags1 = data_021fbe40[1];
        if (flags1 & 1) {
            func_ov128_0229bc10(self);
            return;
        }
        if (flags1 & 0x800) {
        flag_800:;
            func_ov128_0229b7cc(self, 2);
            func_ov002_02208098((void *) (self), 4);
            func_ov128_0229bc88(self);
            return;
        }
    }
    {
        int old1 = self->unk_2D48;
        int old2 = self->unk_2D4C;
        int *p48;
        if (data_021fbe40[0] & 0x20) {
            *(&self->unk_2D48) = old1 - 4;
        } else if (data_021fbe40[0] & 0x10) {
            *(&self->unk_2D48) = old1 + 4;
        }
        if (data_021fbe40[0] & 0x40) {
            self->unk_2D4C -= 4;
        } else if (data_021fbe40[0] & 0x80) {
            self->unk_2D4C += 4;
        }
        if ((old1 == self->unk_2D48) && (old2 == self->unk_2D4C)) {
            return;
        }
        if (self->unk_2D48 < 0x30) {
            self->unk_2D48 = 0x30;
            func_ov127_02299b58(&self->unk_4A4, -4);
            func_ov128_0229bb20(self);
        } else if (self->unk_2D48 > 0xd0) {
            self->unk_2D48 = 0xd0;
            func_ov127_02299b58(&self->unk_4A4, 4);
            func_ov128_0229bb20(self);
        }
        if (self->unk_2D4C < 0x20) {
            self->unk_2D4C = 0x20;
            func_ov127_02299abc(&self->unk_4A4, -4, 0);
            func_ov128_0229bb20(self);
        } else if (self->unk_2D4C > 0xa0) {
            self->unk_2D4C = 0xa0;
            func_ov127_02299abc(&self->unk_4A4, 4, 0);
            func_ov128_0229bb20(self);
        }
        func_ov002_0220a0b4(&self->unk_110, self->unk_2D48, self->unk_2D4C);
    }
}
