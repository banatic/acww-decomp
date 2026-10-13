/* func_02055140 @ 0x02055140, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056548(int, int *, int);
extern int data_020dd030;

typedef struct {
    unsigned char pad_00[0x5C];
    int unk_5C;
    unsigned char pad_60[0x54];
    int unk_B4;
} UnkStruct_02055140;

int func_02055140(UnkStruct_02055140 *self, int a)
{
    if (self->unk_B4 != 0) {
        goto L_return0;
    }
    if (self->unk_5C != 0) {
        goto L_call;
    }
L_return0:
    return 0;
L_call:
    self->unk_B4 = func_02056548(self->unk_5C, &data_020dd030, a);
    if (self->unk_B4 == 0) {
        return 0;
    }
    return 1;
}
