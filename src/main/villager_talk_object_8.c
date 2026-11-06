/* villager_talk_object_8: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02025fec @ 0x02025fec, 0x6c bytes, Thumb
 * func_02025fe4 @ 0x02025fe4, 0x8 bytes, Thumb
 * func_02025f78 @ 0x02025f78, 0x6c bytes, Thumb
 * func_02025ee0 @ 0x02025ee0, 0x98 bytes, Thumb
 * func_02025e70 @ 0x02025e70, 0x70 bytes, Thumb
 * func_02025de8 @ 0x02025de8, 0x88 bytes, Thumb
 * func_02025d2c @ 0x02025d2c, 0xbc bytes, Thumb
 */

typedef struct {
    char pad_00[0x20];
    unsigned char level;
    unsigned char sublevel;
} UnkStruct_02025fec;

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02025f78;

struct UnkStruct_02025ee0 {
    char pad_00[0x100];
    int *unk_100;
    char pad_104[0x60];
    int *unk_164;
};

typedef struct {
    void *ptr;
    unsigned char byte;
} Param1;

typedef struct SubB {
    char pad_00[0x830];
    int unk_830;
} SubB;

typedef struct UnkStruct_02025de8 {
    char pad_00[0x100];
    SubB *unk_100;
    char pad_104[0x20];
    char buf_124[0x40];
    int *unk_164;
} UnkStruct_02025de8;

typedef struct UnkStruct_02025d2c {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02025d2c;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02025d2c_2 {
    char pad_00[0x100];
    UnkStruct_02025d2c *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[0x164 - 0x123];
    int unk_164;
} UnkStruct_02025d2c_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02025d2c_3;

extern void func_0201cfb4(void *self, void *local);
extern void func_0201cf90(void *self, void *local, int idx, int a, int b, void *ptr);
extern void func_0201cec8(void *self, void *local);
extern void func_0202da74(void *self, Pair p);
extern void func_02068388(int field, int flag);
extern int data_021c2ca4;
extern int data_021c2cbc;
extern Pair data_020d9380;
extern struct {
    int a;
    unsigned char b;
} data_020c8d50;
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern void *func_0209b91c(int *);
extern int func_0209bd44(void *);
extern unsigned int func_0202d9c4(void *);
extern int func_020984e8(void);
extern int func_02099870(int object);
extern void func_0209b9cc(int *, int, void *, int, int);
extern void func_020784f8(int, int, void *, int, int);
extern int func_0207f270(int);
extern int func_020794d0(int);
extern void func_0209bd5c(void *);
extern int *data_020ccf94;
extern struct Data1 {
    int unk_00;
    unsigned char unk_04;
} data_020c8d48;
extern struct Pair {
    int a;
    int b;
} data_020d9370;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202db48(void *, struct Pair);
extern int func_0209bc40(int);
extern Cfg data_020d9308;
extern int *data_020d9d10[5];
extern int func_0209b914(int x);
extern int func_0209bcc4(int x, int *idx);
extern int func_0209b8d0(int x);

void func_02025ee0(struct UnkStruct_02025ee0 *self);

void func_02025fec(void *self)
{
    UnkStruct_02025fec local;

    func_0201cfb4(self, &local);
    func_0201cf90(self, &local, 0, 0x1f, 0x1f, &data_021c2ca4);
    func_0201cf90(self, &local, 1, 0x20, 0x20, &data_021c2cbc);

    local.level = 2;
    local.sublevel = local.level - 1;

    func_0201cec8(self, &local);
    func_0202da74(self, data_020d9380);
    func_02068388(*(int *) ((char *) self + 0x40), 1);
}

void func_02025fe4(void *argument0)
{
    func_02025ee0((struct UnkStruct_02025ee0 *) ((void *) argument0));
}

void func_02025f78(void *self, UnkStruct_02025f78 *out)
{
    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e,
                  func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(
                      *(int *) (*(char **) ((char *) self + 0x100) + 0x830)))),
                  data_020c8d50.a, data_020c8d50.b, 0, 0);
    out->p = (char *) self + 0x104;
    out->b = *((unsigned char *) self + 0x122);
    *(unsigned short *) ((char *) self + 0x15a) = 0x5e;
}

void func_02025ee0(struct UnkStruct_02025ee0 *self)
{
    int forwarded_value;

    int r7;
    int r6 = *((int *) ((char *) self->unk_100 + 0x830));
    int flag = 0;

    if (func_0209bd44((void *) func_0209b91c(self->unk_164)) == 0) {
        r7 = func_0209bc40((int) ((unsigned char *) func_0202d9c4(self)));
        flag = 1;
    } else {
        r7 = func_0209bc40((int) ((unsigned char *) func_0209b91c(self->unk_164)));
    }

    (forwarded_value = (int) func_020984e8());
    {
        int temp = func_02099870((int) forwarded_value);
        func_0209b9cc(self->unk_164, r7, (char *) self + 0x124, temp, flag);
    }

    func_020784f8(r6, r7, (char *) self + 0x124, data_020ccf94[25], flag);

    func_0209bd5c((void *) func_020794d0((int) func_0207f270(r6)));
}

void func_02025e70(void *param0, Param1 *param1)
{
    struct {
        int a;
        int b;
        int c;
        int d;
        int e;
    } local;

    local.a = func_020036e8(func_0208150c(*(int *) ((char *) (*(void **) ((char *) param0 + 0x100)) + 0x830)));
    local.b = data_020c8d48.unk_00;
    local.c = data_020c8d48.unk_04;
    local.d = 0;
    local.e = 0;

    func_0202da38(param0, (char *) param0 + 0x104, (char *) param0 + 0x122, 30, local.a, local.b, local.c, local.d, local.e);
    param1->ptr = (char *) param0 + 0x104;
    param1->byte = *(unsigned char *) ((char *) param0 + 0x122);

    func_0202db48(param0, data_020d9370);
}

void func_02025de8(UnkStruct_02025de8 *p)
{
    int r4, r7, r6;
    r6 = p->unk_100->unk_830;
    r4 = 0;
    if (func_0209bd44((void *) (int) func_0209b91c(p->unk_164)) == 0) {
        r7 = func_0209bc40((int) func_0202d9c4((void *) p));
        r4 = 1;
    } else {
        r7 = func_0209bc40((int) func_0209b91c(p->unk_164));
    }
    func_0209b9cc(p->unk_164, r7, (void *) p->buf_124, 0, r4);
    func_020784f8(r6, r7, (void *) p->buf_124, 4, r4);
    func_0209bd5c((void *) (func_020794d0(func_0207f270(r6))));
}

void func_02025d2c(UnkStruct_02025d2c_2 *self, UnkStruct_02025d2c_3 *out)
{
    // DECLS
    Cfg cfg;
    int idx;
    int a;
    int b;
    // ENDDECLS

    cfg = data_020d9308;
    a = func_0209b914(self->unk_164);
    b = func_0209bc40((int) func_0202d9c4((void *) self));
    idx = 0;
    func_0209bcc4((int) func_0202d9c4((void *) self), &idx);
    if (a < func_0209b8d0(b)) {
        if (idx < 5) {
            cfg.unk_00 = data_020d9d10[idx][a];
        }
    }
    if (cfg.unk_00 != 0) {
        func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e,
                      func_020036e8(func_0208150c(self->unk_100->unk_830)), cfg.unk_00, cfg.unk_04, 0, 0);
    }
    out->p = self->unk_104;
    out->b = self->unk_122;
}
