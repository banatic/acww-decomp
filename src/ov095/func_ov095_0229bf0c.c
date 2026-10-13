/* func_ov095_0229bf0c @ 0x0229bf0c, 0x30 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    unsigned char pad_1D[0x23];
    unsigned char unk_40;
} UnkStruct_0229bf0c;

int func_ov095_0229bf0c(UnkStruct_0229bf0c *p)
{
    unsigned char v = p->unk_1C;
    if (v > 1) {
        p->unk_1C = v - 1;
    }

    if (p->unk_40) {
        p->unk_40--;
    } else {
        p->unk_40 = 1;
        return 1;
    }
    return 0;
}
