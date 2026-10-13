/* func_ov003_02222c68 @ 0x02222c68, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    char pad_04[200];
    int unk_CC;
    int unk_D0;
    int pad_D4;
    int unk_D8;
    char pad_138[92];
    int arr_138[3];
    int unk_144;
    int unk_148;
} UnkStruct_02222c68;

void func_ov003_02222c68(UnkStruct_02222c68 *self)
{
    int i;
    self->unk_00 = 0;
    self->unk_D8 = 0;
    self->unk_CC = -1;
    self->unk_D0 = -1;
    for (i = 0; i < 3; i++) {
        self->arr_138[i] = -1;
    }
    self->unk_144 = 0;
    self->unk_148 = 0;
}
