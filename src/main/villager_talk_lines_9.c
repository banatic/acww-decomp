/* villager_talk_lines_9: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201fd78 @ 0x0201fd78, 0x64 bytes, Thumb
 * func_0201fd14 @ 0x0201fd14, 0x64 bytes, Thumb
 * func_0201fcb0 @ 0x0201fcb0, 0x64 bytes, Thumb
 */

struct UnkStruct_0201fd78 {
    char pad_00[0x830];
    int value;
};

struct In {
    char pad_00[0x100];
    struct UnkStruct_0201fd78 *ptr;
    char buffer[0x1e];
    unsigned char flag;
};

struct UnkStruct_0201fd78_2 {
    char *buf;
    unsigned char flag;
};

typedef struct {
    unsigned char pad_00[0x100];
    int *unk_100;
    unsigned char sub_0x104[0x1e];
    unsigned char unk_122;
} InputStruct;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_0201fd14;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} OutputStruct;

struct UnkStruct_0201fcb0 {
    unsigned char pad_00[0x100];
    unsigned char *unk_100;
    unsigned char buf[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_0201fcb0_2 {
    void *ptr;
    unsigned char unk_04;
};

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(struct In *self, char *buf, unsigned char *flag, int size, int v0, int v1, int v2, int v3, int v4);
extern struct {
    int word;
    unsigned char byte;
} data_020c8ce8;

void func_0201fd78(struct In *self, struct UnkStruct_0201fd78_2 *out)
{
    int v0, v1, v2, v3, v4;

    v0 = func_020036e8(func_0208150c(self->ptr->value));
    v1 = data_020c8ce8.word;
    v2 = 1;
    v3 = 14;
    v4 = data_020c8ce8.byte;

    func_0202da38(self, self->buffer, &self->flag, 30, v0, v1, v2, v3, v4);

    out->buf = self->buffer;
    out->flag = self->flag;
}

void func_0201fd14(InputStruct *p, OutputStruct *out)
{
    int v = func_020036e8(func_0208150c(*(int *) ((char *) p->unk_100 + 0x830)));
    func_0202da38((struct In *) p, (char *) ((char *) p + 0x104), (unsigned char *) ((char *) p + 0x122), 0x1e, v, (*(UnkStruct_0201fd14 *) &data_020c8ce8).unk_00, 1, 0xa, (*(UnkStruct_0201fd14 *) &data_020c8ce8).unk_04);
    out->unk_00 = (char *) p + 0x104;
    out->unk_04 = p->unk_122;
}

void func_0201fcb0(struct UnkStruct_0201fcb0 *self, struct UnkStruct_0201fcb0_2 *out)
{
    int v1;
    int v2;

    v1 = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(*(int *) (self->unk_100 + 0x830))));
    v2 = (*(int *) &data_020c8ce8);
    func_0202da38((struct In *) self, (char *) self->buf, &self->unk_122, 0x1e, v1, v2, 1, 0x4, 3);
    out->ptr = self->buf;
    out->unk_04 = self->unk_122;
}
