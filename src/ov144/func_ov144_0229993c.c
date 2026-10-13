/* func_ov144_0229993c @ 0x0229993c, 0x2a bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov144_02299968(void *);

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0x19];
    unsigned char unk_C1;
} UnkStruct_0229993c;

void func_ov144_0229993c(UnkStruct_0229993c *self)
{
    if (func_ov144_02299968(self) == 0) {
        if (self->unk_A4 > 0) {
            self->unk_C1 = 10;
        } else {
            self->unk_C1 = 9;
        }
    }
}
