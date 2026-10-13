/* func_ov142_0229a954 @ 0x0229a954, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229a6f8(void *a, void *b, int c, int d, int e);

typedef struct {
    char pad_00[0xC8];
    unsigned short unk_C8;
    char pad_CA[0x10];
    unsigned short unk_DA;
    char pad_DC[0x1184];
    char unk_1260;
} UnkStruct_0229a954;

void func_ov142_0229a954(UnkStruct_0229a954 *self)
{
    self->unk_DA = 0;
    self->unk_C8 = (unsigned short) func_ov142_0229a6f8(self, &self->unk_1260, 0x1144, 0x44, 2);
}
