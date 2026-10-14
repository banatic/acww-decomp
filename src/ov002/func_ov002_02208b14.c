/* func_ov002_02208b14 @ 0x02208b14, 0x5e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209324(void *self);
extern int func_ov002_02209318(void *self);

struct UnkStruct_02208b14 {
    unsigned char pad_00[8];
    int unk_08;
    int unk_0C;
    unsigned char pad_10[0xc];
    unsigned char unk_1C;
};

int func_ov002_02208b14(struct UnkStruct_02208b14 *self, int a, int b, int c)
{
    int r7;
    int r4;
    int w;
    int v;
    int i;
    int n;

    r7 = -self->unk_08;
    r4 = -self->unk_0C;
    w = r7 + func_ov002_02209324(self);
    v = r4 + func_ov002_02209318(self);
    if (r7 > a || w < a) {
        return c;
    }
    if (r4 > b || v < b) {
        return c;
    }
    r4 += 0x18;
    i = 0;
    n = self->unk_1C - 1;
    while (i < n) {
        if (r4 > b) {
            return i;
        }
        r4 += 0x10;
        i++;
    }
    return i;
}
