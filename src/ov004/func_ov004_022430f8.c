/* func_ov004_022430f8 @ 0x022430f8, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022430f8 {
    char unk_00[0x50];
    unsigned char unk_50;
    char unk_51[0x192 - 0x51];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
} UnkStruct_022430f8;

extern int func_ov004_02245174(UnkStruct_022430f8 *self);
extern int func_ov004_02245188(UnkStruct_022430f8 *self);

int func_ov004_022430f8(UnkStruct_022430f8 *self)
{
    unsigned char s;
    int m;
    short a;

    s = self->unk_50;
    if (self->unk_196 == 0x34) {
        m = func_ov004_02245174(self);
    } else {
        m = func_ov004_02245188(self);
    }
    if (m != 0) {
        a = self->ang;
        if (m == 3) {
            if (s == 1 || s == 0xa) {
                a -= 0xaaa;
            } else {
                a += 0xaaa;
            }
        } else if (m == 1 || s == 1) {
            a -= 0x38e;
            s = 1;
        } else if (m == 2 || s == 2) {
            a += 0x38e;
            s = 2;
        }
        self->ang = a;
    } else if (s < 0xa) {
        s = (unsigned char) (0xa * s);
    }
    self->unk_50 = s;
    return m;
}
