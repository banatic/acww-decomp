/* func_ov096_0229ea5c @ 0x0229ea5c, 0x2c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229ea5c {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
    char pad_AC[0x2454];
    char unk_2500[1];
} UnkStruct_0229ea5c;

extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);

int func_ov096_0229ea5c(UnkStruct_0229ea5c *self)
{
    self->unk_A4 = func_ov002_02209f3c(self->unk_2500) - 2;
    {
        int result = func_ov002_02209f14(self->unk_2500) - 4;
        self->unk_A8 = result;
        return result;
    }
}
