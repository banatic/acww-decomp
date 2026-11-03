/* villager_talk_lines_7: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201f69c @ 0x0201f69c, 0x9c bytes, Thumb
 * func_0201f638 @ 0x0201f638, 0x64 bytes, Thumb
 * func_0201f5d4 @ 0x0201f5d4, 0x64 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x100];
    char *ptr;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0201f69c;

typedef struct {
    char *unk_00;
    unsigned char unk_04;
} UnkStruct_0201f69c_2;

struct UnkStruct_0201f638 {
    char pad_00[0x100];
    void *unk_100;
    char buffer[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_0201f638_2 {
    void *ptr;
    unsigned char byte;
};

typedef struct SubA {
    char pad_00[0x830];
    void *unk_830;
} SubA;

typedef struct UnkStruct_0201f5d4 {
    char pad_00[0x100];
    SubA *unk_100;
    unsigned char unk_104[30];
    unsigned char unk_122;
} UnkStruct_0201f5d4;

typedef struct UnkStruct_0201f5d4_2 {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201f5d4_2;

typedef struct GlobalT {
    int unk_00;
    unsigned char unk_04;
} GlobalT;

extern int func_0203fdc4(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int data_020c8bd8;
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

void func_0201f69c(UnkStruct_0201f69c *base, UnkStruct_0201f69c_2 *out)
{
    int val, r4, r6, a5, a6, a7, a8, a9;

    val = func_0203fdc4(14);
    if (val < 0) {
        val = 0;
    }

    if (val == 0) {
        r4 = 2;
        r6 = 0;
    } else if (val >= 1 && val <= 2) {
        r4 = 3;
        r6 = 2;
    } else if (val >= 3 && val <= 5) {
        r4 = 3;
        r6 = 5;
    } else {
        r4 = 2;
        r6 = 8;
    }

    a5 = func_020036e8(func_0208150c(*(int *) (base->ptr + 0x830)));
    a6 = data_020c8bd8;
    a7 = 1;
    a8 = r6;
    a9 = (unsigned char) r4;

    func_0202da38((void *) base, (void *) base->unk_104, (void *) (&base->unk_122), 30, a5, a6, a7, a8, a9);

    out->unk_00 = base->unk_104;
    out->unk_04 = base->unk_122;
}

void func_0201f638(struct UnkStruct_0201f638 *p1, struct UnkStruct_0201f638_2 *p2)
{
    void *ptr = *((void **) ((char *) p1->unk_100 + 0x830));
    int result = func_020036e8(func_0208150c((int) ptr));
    func_0202da38(p1, p1->buffer, &p1->unk_122, 0x1e, result, *(int *) &data_020c8bd8, 1, 13,
                  ((unsigned char *) &data_020c8bd8)[4]);
    p2->ptr = p1->buffer;
    p2->byte = p1->unk_122;
}

void func_0201f5d4(UnkStruct_0201f5d4 *self, UnkStruct_0201f5d4_2 *out)
{
    int v1, v2, v3, v4, v5;

    v1 = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) self->unk_100->unk_830)));
    v2 = (*(GlobalT *) &data_020c8bd8).unk_00;
    v3 = 1;
    v4 = 10;
    v5 = (*(GlobalT *) &data_020c8bd8).unk_04;

    func_0202da38(self, &self->unk_104, &self->unk_122, 30, v1, v2, v3, v4, v5);

    out->ptr = &self->unk_104;
    out->byte = self->unk_122;
}
