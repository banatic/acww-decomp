/* func_ov095_0229bf48 @ 0x0229bf48, 0x28 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229bf48 {
    char pad_00[0x1c];
    unsigned char unk_1C;
} UnkStruct_0229bf48;

extern void func_ov095_0229cce0(UnkStruct_0229bf48 *self);

int func_ov095_0229bf48(UnkStruct_0229bf48 *self)
{
    if (self->unk_1C != 0) {
        self->unk_1C--;
        if (self->unk_1C >= 4) {
            return 1;
        } else {
            if (self->unk_1C == 0) {
                func_ov095_0229cce0(self);
            }
        }
    }
    return 0;
}
