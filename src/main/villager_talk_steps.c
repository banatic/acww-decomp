/* villager_talk_steps: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02023504 @ 0x02023504, 0x64 bytes, Thumb
 * func_020234a0 @ 0x020234a0, 0x64 bytes, Thumb
 * func_0202343c @ 0x0202343c, 0x64 bytes, Thumb
 * func_020233ac @ 0x020233ac, 0x90 bytes, Thumb
 * func_02023348 @ 0x02023348, 0x64 bytes, Thumb
 * func_020232d4 @ 0x020232d4, 0x74 bytes, Thumb
 * func_02023260 @ 0x02023260, 0x74 bytes, Thumb
 * func_020231fc @ 0x020231fc, 0x64 bytes, Thumb
 */

struct GlobalData {
    unsigned int unk_00;
    unsigned char unk_04;
};

typedef struct {
    unsigned int a;
    unsigned char b;
} GlobalData;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020234a0;

struct UnkStruct_0202343c {
    unsigned char pad_00[0x830];
    unsigned int unk_830;
};

struct UnkStruct_0202343c_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_0202343c *inner;
    char emb[30];
    unsigned char flag;
};

struct Output {
    void *ptr;
    unsigned char flag;
};

struct GlobalData_0202343c {
    int word;
    unsigned char byte;
};

typedef struct {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_020233ac {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_020233ac;

typedef struct UnkStruct_020233ac_2 {
    char pad_00[0x100];
    UnkStruct_020233ac *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[0x15a - 0x123];
    unsigned short unk_15A;
} UnkStruct_020233ac_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_020233ac_3;

struct GlobalData_020232d4 {
    int x;
    unsigned char y;
};

struct UnkStruct_020232d4 {
    char pad_00[0x830];
    void *unk_830;
};

struct UnkStruct_020232d4_2 {
    char pad_00[0x100];
    void *unk_100;
    char buf_104[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_020232d4_3 {
    void *ptr;
    unsigned char byte;
};

typedef struct {
    char pad_00[0x100];
    void *ptr;
    char arr[0x1E];
    unsigned char byte;
} UnkStruct_02023260;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02023260_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02023260_3;

struct UnkStruct_020231fc_2 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_020231fc {
    char pad_00[0x100];
    struct UnkStruct_020231fc_2 *inner;
    char buffer[30];
    unsigned char byte;
};

struct Global {
    int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_020231fc_3 {
    void *ptr;
    unsigned char byte;
};

extern int func_020036e8(int v);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern struct GlobalData data_020c8bd0;
extern int func_0208150c(int);
extern GlobalData data_020c8bc0;
extern struct GlobalData_0202343c data_020c8bb0;
extern Cfg data_020c8e30;
extern Pair data_020d8e90;
extern void func_0206f80c(Pair *v);
extern void func_02029264(UnkStruct_020233ac_2 *self, Pair *v);
extern void func_0202db48(UnkStruct_020233ac_2 *self, Pair p);
extern int func_020984e8(void);
extern void func_0209ae70(void *, int, void *);
extern int func_0207f270(int);
extern int func_020794d0(int);
extern void func_0209bd5c(int);
extern void func_0207b57c(void *);
extern unsigned char data_021e5a2c[];
extern void *func_02099640(int);
extern struct GlobalData_020232d4 data_020c8e18;
extern void func_0209af04(void *);
extern UnkStruct_02023260_3 data_020c8e08;
extern struct Global data_020c8a28;

void func_02023504(void *self, void *out)
{
    int arg4;
    int arg5;
    int arg6;

    arg4 = func_020036e8(func_0208150c((int) (*(void **) ((char *) (*(void **) ((char *) self + 0x100)) + 0x830))));
    arg5 = data_020c8bd0.unk_00;
    arg6 = data_020c8bd0.unk_04;

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 30, arg4, arg5, arg6, 0, 0);

    *(void **) out = (char *) self + 0x104;
    *(unsigned char *) ((char *) out + 4) = *(unsigned char *) ((char *) self + 0x122);
}

void func_020234a0(void *p, UnkStruct_020234a0 *out)
{
    int val0;

    val0 = func_020036e8(func_0208150c(*(unsigned int *) ((char *) *(unsigned int *) ((char *) p + 0x100) + 0x830)));
    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 0x1e, val0, data_020c8bc0.a, data_020c8bc0.b, 0, 0);
    out->ptr = (char *) p + 0x104;
    out->byte = *(unsigned char *) ((char *) p + 0x122);
}

void func_0202343c(struct UnkStruct_0202343c_2 *self, struct Output *out)
{
    int x;
    x = func_020036e8(func_0208150c(self->inner->unk_830));
    func_0202da38(self, &self->emb, &self->flag, 30, x, data_020c8bb0.word, data_020c8bb0.byte, 0, 0);
    out->ptr = &self->emb;
    out->flag = self->flag;
}

void func_020233ac(UnkStruct_020233ac_2 *self, UnkStruct_020233ac_3 *out)
{
    Pair v;

    v.a = 0;
    v.b = 0;
    func_0206f80c(&v);
    func_02029264(self, &v);
    func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), data_020c8e30.unk_00, data_020c8e30.unk_04, 0, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
    self->unk_15A = 0x5e;
    func_0202db48(self, data_020d8e90);
}

void func_02023348(void *param)
{
    void *p4;
    int local[2];
    int r1;

    p4 = (void *) func_02099640(func_020984e8());
    local[0] = 0;
    local[1] = 0;
    func_0206f80c((Pair *) local);
    r1 = func_0208150c(*(int *) (*(char **) ((char *) param + 0x100) + 0x830));
    p4 = (char *) p4 + 0xa4;
    func_0209ae70(p4, r1, local);
    func_0209bd5c(func_020794d0(func_0207f270(*(int *) (*(char **) ((char *) param + 0x100) + 0x830))));
    func_0207b57c((void *) data_021e5a2c);
}

void func_020232d4(struct UnkStruct_020232d4_2 *a, struct UnkStruct_020232d4_3 *out)
{
    func_02029264((UnkStruct_020233ac_2 *) a, (Pair *) ((void *) ((char *) func_02099640((int) func_020984e8()) + 0xc0)));
    func_0202da38(a, a->buf_104, &a->unk_122, 0x1e, (int) ((void *) func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) (((struct UnkStruct_020232d4 *) a->unk_100)->unk_830))))), data_020c8e18.x, data_020c8e18.y, 0, 0);
    out->ptr = a->buf_104;
    out->byte = a->unk_122;
}

void func_02023260(UnkStruct_02023260 *self, UnkStruct_02023260_2 *out)
{
    int a, b, c, d, e, x;
    void *p;

    p = func_02099640((int) func_020984e8());
    x = *(int *) ((char *) self->ptr + 0x830);
    a = func_020036e8(func_0208150c(x));
    b = data_020c8e08.unk_00;
    c = data_020c8e08.unk_04;
    d = 0;
    e = 0;
    func_0202da38(self, self->arr, &self->byte, 30, a, b, c, d, e);
    out->ptr = self->arr;
    out->byte = self->byte;
    func_0209af04((char *) p + 0xa4);
}

void func_020231fc(struct UnkStruct_020231fc *p, struct UnkStruct_020231fc_3 *out)
{
    struct {
        int a;
        int b;
        int c;
        int d;
        int e;
    } local;

    local.a = func_020036e8(func_0208150c(p->inner->unk_830));
    local.b = data_020c8a28.unk_00;
    local.c = data_020c8a28.unk_04;
    local.d = 0;
    local.e = 0;

    func_0202da38((void *) p, (void *) p->buffer, (void *) (&p->byte), 30, local.a, local.b, local.c, local.d, local.e);
    out->ptr = p->buffer;
    out->byte = p->byte;
}
