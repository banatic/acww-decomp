/* villager_talk_lines_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201f380 @ 0x0201f380, 0x8c bytes, Thumb
 * func_0201f31c @ 0x0201f31c, 0x64 bytes, Thumb
 * func_0201f2b8 @ 0x0201f2b8, 0x64 bytes, Thumb
 */

struct UnkStruct_0201f380 {
    void *unk_00;
    unsigned char unk_04;
};

typedef struct {
    char pad_00[0x830];
    int unk_830;
} PtrStruct;

typedef struct {
    char pad_00[0x100];
    PtrStruct *p;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_0201f31c;

typedef struct {
    void *ptr;
    unsigned char flag;
} UnkStruct_0201f31c_2;

typedef struct UnkStruct_0201f2b8_3 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0201f2b8_3;

typedef struct UnkStruct_0201f2b8 {
    char pad_00[0x100];
    UnkStruct_0201f2b8_3 *inner;
    unsigned char buf[0x20];
} UnkStruct_0201f2b8;

typedef struct UnkStruct_0201f2b8_2 {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201f2b8_2;

extern int func_0203fdc4(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern int data_020c8ba0;

void func_0201f380(char *a, struct UnkStruct_0201f380 *b)
{
    int x;
    int r4, r6;

    x = func_0203fdc4(0x10);
    if (x < 0) {
        x = 0;
    }

    if (x == 0) {
        r4 = 2;
        r6 = 0;
    } else if (x >= 1 && x <= 5) {
        r4 = 3;
        r6 = 2;
    } else {
        r4 = 2;
        r6 = 5;
    }

    func_0202da38(a, a + 0x104, a + 0x122, 0x1e, func_020036e8(func_0208150c(*(int *) (*(int *) (a + 0x100) + 0x830))),
                  data_020c8ba0, 1, r6, (unsigned char) r4);

    b->unk_00 = a + 0x104;
    b->unk_04 = *(unsigned char *) (a + 0x122);
}

void func_0201f31c(UnkStruct_0201f31c *self, UnkStruct_0201f31c_2 *out)
{
    int val = func_020036e8(func_0208150c(self->p->unk_830));
    func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e, val,
                  (*(struct {
                      int field0;
                      unsigned char field4;
                  } *) &data_020c8ba0)
                      .field0,
                  1, 10,
                  (*(struct {
                      int field0;
                      unsigned char field4;
                  } *) &data_020c8ba0)
                      .field4);
    out->ptr = self->unk_104;
    out->flag = self->unk_122;
}

void func_0201f2b8(UnkStruct_0201f2b8 *s, UnkStruct_0201f2b8_2 *out)
{
    func_0202da38((void *) s, (void *) s->buf, (void *) (&s->buf[0x1e]), 30, func_020036e8(func_0208150c(s->inner->unk_830)),
                  (*(struct {
                      int word;
                      unsigned char byte;
                  } *) &data_020c8ba0)
                      .word,
                  1, 7,
                  (*(struct {
                      int word;
                      unsigned char byte;
                  } *) &data_020c8ba0)
                      .byte);
    out->ptr = s->buf;
    out->byte = s->buf[0x1e];
}
