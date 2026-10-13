/* func_02055d80 @ 0x02055d80, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char *unk_5C;
} UnkStruct_02055d80;

void func_02055d80(UnkStruct_02055d80 *self, int v)
{
    int i;
    unsigned char *base;
    unsigned short w;
    unsigned short h;
    unsigned char *p;
    unsigned int val;
    unsigned char *q;
    unsigned int mask;
    unsigned int off;
    unsigned char *arr;
    base = self->unk_5C + *(unsigned int *) (self->unk_5C + 8);
    i = 0;
    val = (unsigned int) v << 24;
    arr = base + 4;
    mask = 0xc0ffffff;
    while (i < (int) *(unsigned char *) (self->unk_5C + 0x18)) {
        h = *(unsigned short *) (base + 0xa);
        q = arr + h;
        w = *(unsigned short *) (arr + h);
        off = *(unsigned int *) (q + w * i + 4);
        p = base + off;
        *(unsigned int *) (p + 0xc) &= mask;
        *(unsigned int *) (p + 0xc) |= val;
        i++;
    }
}
