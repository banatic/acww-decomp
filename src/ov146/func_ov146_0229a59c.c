/* func_ov146_0229a59c @ 0x0229a59c, 0x4c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov002_0220a4d4(void *p);

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned int unk_A8;
    unsigned char pad_AC[6];
    unsigned char unk_B2;
} UnkStruct_0229a59c;

unsigned int func_ov146_0229a59c(UnkStruct_0229a59c *self)
{
    unsigned char b = self->unk_B2;
    if (b >= 3 && b <= 9) {
        return 0x40 + (b - 3) * 16 - (self->unk_A8 & 0xf);
    } else {
        switch (b) {
            case 0:
            case 1:
                return 0xad;
            case 2:
                return func_ov002_0220a4d4((unsigned char *) self + 0x1fb4);
            default:
                return 0x60;
        }
    }
}
