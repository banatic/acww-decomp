/* func_ov142_02299938 @ 0x02299938, 0x6c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299938 UnkStruct_02299938;
struct UnkStruct_02299938 {
    unsigned char pad_00[0x9c];
    unsigned int unk_9C;
    unsigned int unk_A0;
    unsigned int unk_A4;
    unsigned char pad_A8[0xb4 - 0xa8];
    short unk_B4;
};

extern int func_ov142_0229a6d8(UnkStruct_02299938 *self);
extern void func_ov142_0229a4d4(UnkStruct_02299938 *self, int value);
extern void func_ov142_02299a54(UnkStruct_02299938 *self);
extern void func_ov142_022999ec(UnkStruct_02299938 *self);
extern void func_ov142_02299a08(UnkStruct_02299938 *self);
extern void func_ov142_02299648(UnkStruct_02299938 *self, int value);

void func_ov142_02299938(UnkStruct_02299938 *self)
{
    int r5;
    int result;

    r5 = self->unk_B4;
    result = func_ov142_0229a6d8(self) - 8;
    if (result < 0) {
        result = 0;
    }
    if (r5 < 0) {
        r5 = 0;
    } else if (r5 > result) {
        r5 = result;
    }

    func_ov142_0229a4d4(self, r5 * 16);

    self->unk_A0 = self->unk_9C;
    func_ov142_02299a54(self);

    if (self->unk_A4 == 0) {
        func_ov142_022999ec(self);
    } else {
        func_ov142_02299a08(self);
    }

    func_ov142_02299648(self, 0x200);
}
