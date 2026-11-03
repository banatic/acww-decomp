/* bbs_write_text_4: 4 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229f6d4 @ 0x0229f6d4, 0xe bytes, Thumb
 * func_ov112_0229f6b8 @ 0x0229f6b8, 0x1a bytes, Thumb
 * func_ov112_0229f668 @ 0x0229f668, 0x50 bytes, Thumb
 * func_ov112_0229f630 @ 0x0229f630, 0x38 bytes, Thumb
 */

typedef struct UnkStruct_0229f668 {
    unsigned char pad_00[0x98];
    int unk_98;
    int unk_9C;
    unsigned char pad_A0[0x1D];
    unsigned char unk_BD;
    unsigned char pad_BE[6];
    short shorts[1];
    unsigned char pad_C6[0x6B8A];
    int array_6C50[1];
} UnkStruct_0229f668;

struct UnkStruct_0229f630 {
    char pad_00[0x94];
    int count;
    char pad_98[0x6bb8];
    int arr[1];
};

extern int func_02051d08(short *p, int diff);
extern void func_ov112_0229fab4(UnkStruct_0229f668 *self);

int func_ov112_0229f630(struct UnkStruct_0229f630 *p, int val);

void func_ov112_0229f6d4(char *r0, char r1)
{
    char *r2 = r0 + 0xbd;
    *r2 = r1;
    *(r0 + 0xbc) = 0x10;
}

unsigned short func_ov112_0229f6b8(unsigned char *p)
{
    unsigned char n;

    n = p[0xBD];
    if (n == 0) {
        return 0;
    }
    return *(unsigned short *) (p + (n - 1) * 2 + 0xC4);
}

void func_ov112_0229f668(UnkStruct_0229f668 *self)
{
    int val;
    int index;
    short *p;
    int result;

    val = func_ov112_0229f630((struct UnkStruct_0229f630 *) self, (unsigned char) self->unk_BD);
    self->unk_9C = (val << 4) + 0x28;
    index = self->array_6C50[val];
    p = &self->shorts[index];
    result = func_02051d08(p, self->unk_BD - index);
    self->unk_98 = (unsigned char) (result + 0x30);
    func_ov112_0229fab4(self);
}

int func_ov112_0229f630(struct UnkStruct_0229f630 *p, int val)
{
    int i = 0;
    int n = p->count;
    while (i < n) {
        if (val < p->arr[i + 1]) {
            return i;
        }
        i++;
    }
    if (n < 6) {
        return n;
    }
    return 5;
}
