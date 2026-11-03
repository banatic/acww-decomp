/* villager_talk_9: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201e634 @ 0x0201e634, 0x64 bytes, Thumb
 * func_0201e5d0 @ 0x0201e5d0, 0x64 bytes, Thumb
 * func_0201e56c @ 0x0201e56c, 0x64 bytes, Thumb
 */

struct UnkStruct_0201e634 {
    char pad_00[0x830];
    unsigned int unk_830;
};

struct UnkStruct_0201e634_2 {
    char pad_00[0x100];
    struct UnkStruct_0201e634 *unk_100;
    unsigned char unk_104[30];
    unsigned char unk_122;
};

struct UnkStruct_0201e634_3 {
    unsigned char *field0;
    unsigned char unk_04;
};

typedef struct {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1E];
    unsigned char unk_122;
} UnkStruct_0201e5d0_2;

typedef struct {
    char pad_00[0x830];
    int unk_830;
} Field100Type;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GlobalData;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201e5d0;

struct UnkStruct_0201e56c {
    unsigned char pad_00[0x100];
    unsigned char *unk_100;
    unsigned char buf[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_0201e56c_2 {
    void *ptr;
    unsigned char unk_04;
};

extern struct {
    unsigned int field0;
    unsigned char field4;
} data_020c8b50;
extern int func_0208150c(unsigned int);
extern int func_020036e8(int);
extern int func_0202da38(struct UnkStruct_0201e634_2 *, unsigned char *, unsigned char *, int, int, int, int, int, int);

unsigned char func_0201e634(struct UnkStruct_0201e634_2 *s, struct UnkStruct_0201e634_3 *out)
{
    unsigned char c;
    func_0202da38(s, s->unk_104, &s->unk_122, 0x1e, func_020036e8(func_0208150c(s->unk_100->unk_830)), data_020c8b50.field0, 1,
                  0xe, data_020c8b50.field4);
    out->field0 = s->unk_104;
    c = s->unk_122;
    out->unk_04 = c;
    return c;
}

void func_0201e5d0(UnkStruct_0201e5d0_2 *self, UnkStruct_0201e5d0 *out)
{
    int local0;
    local0 = func_020036e8(func_0208150c(((Field100Type *) self->unk_100)->unk_830));
    func_0202da38((struct UnkStruct_0201e634_2 *) self, (unsigned char *) self->unk_104, (unsigned char *) (&self->unk_122), 0x1e, local0, (*(GlobalData *) &data_020c8b50).unk_00, 1, 0x10, (*(GlobalData *) &data_020c8b50).unk_04);
    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}

void func_0201e56c(struct UnkStruct_0201e56c *self, struct UnkStruct_0201e56c_2 *out)
{
    int v1;
    int v2;

    v1 = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(*(int *) (self->unk_100 + 0x830))));
    v2 = (*(int *) &data_020c8b50);
    func_0202da38((struct UnkStruct_0201e634_2 *) self, self->buf, &self->unk_122, 0x1e, v1, v2, 1, 0x12, 3);
    out->ptr = self->buf;
    out->unk_04 = self->unk_122;
}
