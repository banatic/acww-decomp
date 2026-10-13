/* func_ov145_0229996c @ 0x0229996c, 0x56 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0x18];
    unsigned char unk_C0;
} UnkStruct_0229996c;

extern int func_ov145_02299a24(UnkStruct_0229996c *self, unsigned char value);
extern void func_ov145_02299b94(UnkStruct_0229996c *self, int value);
extern void func_ov145_0229a0d0(UnkStruct_0229996c *self);
extern void func_ov145_0229a134(UnkStruct_0229996c *self);

void func_ov145_0229996c(UnkStruct_0229996c *self, unsigned char value)
{
    if (self->unk_C0 == value) {
        return;
    }
    self->unk_C0 = value;
    self->unk_A4 = (func_ov145_02299a24(self, value) - 8) << 4;
    if (self->unk_A4 < 0) {
        self->unk_A4 = 0;
    }
    func_ov145_02299b94(self, 0);
    self->unk_A0 = 0;
    func_ov145_0229a0d0(self);
    func_ov145_0229a134(self);
}
