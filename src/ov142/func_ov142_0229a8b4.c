/* func_ov142_0229a8b4 @ 0x0229a8b4, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov142_0229a76c(void *a1, void *a2, int a3, int a4, int a5);

typedef struct {
    char pad_00[0xd0];
    unsigned short unk_D0;
    char pad_D2[0x10];
    unsigned short unk_E2;
    char pad_E4[0x1584];
    char unk_1668;
} UnkStruct_0229a8b4;

void func_ov142_0229a8b4(UnkStruct_0229a8b4 *self)
{
    self->unk_E2 = 0;
    self->unk_D0 = func_ov142_0229a76c(self, &self->unk_1668, 0x1003, 0x40, 6);
}
