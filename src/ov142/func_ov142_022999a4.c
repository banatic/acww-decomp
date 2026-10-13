/* func_ov142_022999a4 @ 0x022999a4, 0x48 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9C];
    unsigned int unk_9C;
    unsigned int unk_A0;
    char pad_A4[0x14];
    short unk_B8;
    char pad_BA[4];
    unsigned char unk_BE;
} UnkStruct_022999a4;

extern void func_ov142_0229ab80(UnkStruct_022999a4 *s, unsigned char b);
extern void func_ov142_0229a4d4(UnkStruct_022999a4 *s, int value);
extern void func_ov142_02299a54(UnkStruct_022999a4 *s);
extern void func_ov142_022999ec(UnkStruct_022999a4 *s);
extern void func_ov142_02299658(UnkStruct_022999a4 *s, int value);

void func_ov142_022999a4(UnkStruct_022999a4 *self)
{
    func_ov142_0229ab80(self, self->unk_BE);
    func_ov142_0229a4d4(self, (self->unk_B8 - 3) << 4);
    self->unk_A0 = self->unk_9C;
    func_ov142_02299a54(self);
    func_ov142_022999ec(self);
    func_ov142_02299658(self, 0x200);
}
