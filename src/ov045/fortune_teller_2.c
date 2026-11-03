/* fortune_teller_2: 5 functions, module ov045
 * mwccarm 1.2/base -O4,s
 * func_ov045_02260644 @ 0x02260644, 0x24 bytes, Thumb
 * func_ov045_02260630 @ 0x02260630, 0x14 bytes, Thumb
 * func_ov045_02260618 @ 0x02260618, 0x18 bytes, Thumb
 * func_ov045_022605a4 @ 0x022605a4, 0x74 bytes, Thumb
 * func_ov045_02260524 @ 0x02260524, 0x80 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned int word1;
} UnkStruct_02260644;

struct UnkStruct_022605a4 {
    char pad_00[0x744];
    unsigned char unk_744;
    unsigned char unk_745;
    char pad_746[6];
    unsigned char unk_74C;
    char pad_74D[3];
    int unk_750;
};

struct Param {
    char pad_00[0x74c];
    unsigned char c;
    char pad_74D[3];
    unsigned int w;
};

extern void func_0209e474(void *);
extern int data_ov045_022615a0;
extern int func_020644cc(int);
extern struct Entry {
    unsigned char c;
    unsigned int w;
} data_ov045_022611a8[];
extern struct Entry data_ov045_02261230[];

int func_ov045_02260644(void)
{
    UnkStruct_02260644 s;
    s.unk_00 = 0;
    s.word1 = 0;
    func_0209e474(&s);
    if (((unsigned char *) &s)[2] >= 6u) {
        return 0;
    } else {
        return 1;
    }
}

int func_ov045_02260630(void)
{
    return data_ov045_022615a0 + 0x65c;
}

unsigned int func_ov045_02260618(void)
{
    return ((*(unsigned int * *) &data_ov045_022615a0)[0x64] << 4) >> 16;
}

void func_ov045_022605a4(struct UnkStruct_022605a4 *self)
{
    int v;
    int base;

    self->unk_74C = func_020644cc(0x16);

    if (func_020644cc(2) == 0) {
        self->unk_750 = 0;
    } else {
        self->unk_750 = 1;
    }

    v = func_020644cc(2);
    base = self->unk_74C * 2 + 0x1a;
    self->unk_744 = (unsigned char) (base + v + 0x2c * self->unk_750);
    self->unk_745 = (unsigned char) (self->unk_74C + 0x72 + 0x16 * self->unk_750);
}

int func_ov045_02260524(struct Param *p)
{
    unsigned char i;
    i = 0;
    while (i < 0x11) {
        if (p->c == data_ov045_022611a8[i].c && p->w == data_ov045_022611a8[i].w) {
            return 1;
        }
        i++;
    }
    i = 0;
    while (i < 0x15) {
        if (p->c == data_ov045_02261230[i].c && p->w == data_ov045_02261230[i].w) {
            return 2;
        }
        i++;
    }
    return 0;
}
