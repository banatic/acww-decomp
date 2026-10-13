/* func_020c0658 @ 0x020c0658, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[8];
    int unk_08;
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[4];
    int unk_60;
    int unk_64;
} UnkStruct_020c0658;

extern void func_020bf568(UnkStruct_020c0658 *self, int flag, int param);

void func_020c0658(UnkStruct_020c0658 *self)
{
    int flag;

    if (self->unk_08 == 0x28) {
        flag = 1;
    } else {
        flag = 0;
    }

    func_020bf568(self, flag, 0x8000);

    self->unk_0C = 0x13;
    self->unk_58 = 2;
    self->unk_60 = 0;
    self->unk_64 = 0;
}
