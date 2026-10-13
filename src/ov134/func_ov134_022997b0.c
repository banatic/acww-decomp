/* func_ov134_022997b0 @ 0x022997b0, 0x2a bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022997b0 {
    unsigned char pad_00[0xAD];
    unsigned char unk_AD;
    unsigned char pad_AE[2];
    unsigned char unk_B0;
} UnkStruct_022997b0;

extern int func_ov134_02299bcc(UnkStruct_022997b0 *self, int n);

int func_ov134_022997b0(UnkStruct_022997b0 *self)
{
    int n;

    n = self->unk_B0 - 1;
    if (func_ov134_02299bcc(self, n)) {
        return 0;
    }
    self->unk_AD = n;
    return 1;
}
