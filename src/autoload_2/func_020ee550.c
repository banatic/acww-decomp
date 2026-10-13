/* func_020ee550 @ 0x020ee550, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eeacc(int);

typedef struct {
    unsigned char pad_00[0x18];
    int unk_18;
    unsigned char pad_1C[0x2c];
    int unk_48;
} UnkStruct_020ee550;

int func_020ee550(UnkStruct_020ee550 *self)
{
    if (self->unk_48 != 0 && func_020eeacc(self->unk_48) == 0) {
        goto ret0;
    }
    if (self->unk_18 == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}
