/* func_ov003_02222598 @ 0x02222598, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02222860(void *);

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
    char pad_40[4];
    int unk_44;
} UnkStruct_02222598;

void func_ov003_02222598(UnkStruct_02222598 *self)
{
    self->unk_3C += 0x571;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
        func_ov003_02222860(self);
    }
    self->unk_44 = self->unk_3C;
}
