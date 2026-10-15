/* func_ov105_0229c55c @ 0x0229c55c, 0xa0 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c55c {
    unsigned char pad_00[0xa0];
    unsigned char *ptr;
    unsigned char pad_A4[0x21c];
    unsigned char byte;
};

extern int func_020896b8(int, void *, void *, int, int, int, int);
extern char data_ov105_0229fa80[];

void func_ov105_0229c55c(struct UnkStruct_0229c55c *self)
{
    char *base;
    int i, j, a, b, c, d, e;

    base = (char *) self->ptr + 0x80;
    i = 0;
    j = 0;
    a = 0;
    b = 0;
    c = 0;

    do {
        if (i == self->byte) {
            d = 0x52;
            e = 4;
        } else {
            d = 0x50;
            e = 5;
        }
        func_020896b8(1, data_ov105_0229fa80 + j * 8, base, d, -1, 1, a);
        func_020896b8(1, data_ov105_0229fa80 + (j + 1) * 8, base, d, e, 1, b);
        func_020896b8(1, data_ov105_0229fa80 + (j + 2) * 8, base, 0x50, -1, 1, c);
        i++;
        j += 3;
    } while (i < 2);
}
