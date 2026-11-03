/* villager_talk_object: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02024328 @ 0x02024328, 0xb0 bytes, Thumb
 * func_02024288 @ 0x02024288, 0xa0 bytes, Thumb
 * func_02024228 @ 0x02024228, 0x60 bytes, Thumb
 * func_02024194 @ 0x02024194, 0x94 bytes, Thumb
 * func_020240f4 @ 0x020240f4, 0xa0 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct UnkStruct_02024328 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02024328;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02024328_2 {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    UnkStruct_02024328 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02024328_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02024328_3;

typedef struct UnkStruct_02024288 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02024288;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg_02024288;

typedef struct UnkStruct_02024288_2 {
    char pad_00[0xc8];
    Pair unk_C8;
    char pad_D0[0x100 - 0xd0];
    UnkStruct_02024288 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02024288_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02024288_3;

struct UnkStruct_02024228 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02024228_2 {
    char pad_00[0x100];
    struct UnkStruct_02024228 *unk_100;
    char pad_104[0x60];
    int unk_164;
};

struct UnkStruct_02024228_3 {
    char pad_00[0x64];
    int unk_64;
};

typedef struct {
    int a;
    unsigned char b;
} Cfg_020240f4;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_020240f4;

extern Cfg data_020d9208;
extern Pair data_020d8e30;
extern int data_020c8e74;
extern int data_020c8e80;
extern int data_020c8e8c;
extern int func_0209bc40(int x);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern Cfg_02024288 data_020c8fb8[1];
extern Pair data_020d9270;
extern int func_0209bd04(int x);
extern int func_0209bcc4(int x, int *idx);
extern int func_0209b91c(int);
extern void func_0209bb90(int, int);
extern void func_02078648(int, int);
extern int func_02073dd4(struct UnkStruct_02024228_3 *, int);
extern void func_0207d71c(int);
extern int func_0207f270(int);
extern void func_02079478(int);
extern struct UnkStruct_02024228_3 *data_020ccf94;
extern struct TwoWords {
    unsigned int a;
    unsigned int b;
} data_020d9338;
extern unsigned int data_020d9d24[];
extern int func_0202d9c4(void *self);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int offset, int scale, int h, int i);
extern const Cfg_020240f4 data_020d9128;
extern const int data_020d9d38[];
extern const Cfg_020240f4 data_020d9120;
extern void func_0202db48(void *self, Cfg_020240f4 c);

void func_02024328(UnkStruct_02024328_2 *self, UnkStruct_02024328_3 *out)
{
    Cfg cfg;

    cfg = data_020d9208;
    switch (func_0209bc40(func_0202d9c4((void *) self))) {
        case 2:
            cfg.unk_00 = &data_020c8e74;
            break;
        case 3:
            cfg.unk_00 = &data_020c8e80;
            break;
        default:
            cfg.unk_00 = &data_020c8e8c;
            break;
    }
    func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), (int) cfg.unk_00, cfg.unk_04, 0, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
    self->unk_C8 = data_020d8e30;
}

void func_02024288(UnkStruct_02024288_2 *self, UnkStruct_02024288_3 *out)
{
    int idx;
    Cfg_02024288 *cfg;

    cfg = data_020c8fb8;
    if (func_0209bd04(func_0202d9c4((void *) self)) == 0) {
        idx = 0;
        if (func_0209bcc4(func_0202d9c4((void *) self), &idx) != 0) {
            cfg = &data_020c8fb8[idx];
        }
    }
    func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), cfg->unk_00, cfg->unk_04, 0, 0);
    out->p = self->unk_104;
    out->b = self->unk_122;
    self->unk_C8 = data_020d9270;
}

void func_02024228(struct UnkStruct_02024228_2 *self)
{
    int v1;

    v1 = self->unk_100->unk_830;
    func_0209bb90(func_0209b91c(self->unk_164), 3);
    func_02078648(self->unk_100->unk_830, 3);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        func_0207d71c(v1);
        func_02079478(func_0207f270(v1));
    }
}

void func_02024194(void *self, void *out)
{
    struct {
        unsigned int a;
        unsigned int b;
        int c;
    } cond;
    int idx;
    int res, result;
    void *ptr100;
    unsigned int val830;

    *(struct TwoWords *) &cond = data_020d9338;
    cond.c = 0;

    result = func_0202d9c4(self);
    func_0209bcc4(result, &cond.c);

    idx = cond.c;
    if (idx < 5) {
        cond.a = data_020d9d24[idx];
    }

    if (cond.a == 0) {
        return;
    }

    ptr100 = *(void **) ((char *) self + 0x100);
    val830 = *(unsigned int *) ((char *) ptr100 + 0x830);
    res = func_0208150c(val830);
    result = func_020036e8(res);

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, result, cond.a, *((unsigned char *) &cond.b), 0,
                  0);

    *(void **) out = (char *) self + 0x104;
    *((unsigned char *) out + 4) = *((unsigned char *) self + 0x122);
}

void func_020240f4(void *self, UnkStruct_020240f4 *out)
{
    Cfg_020240f4 cfg;
    int idx;

    cfg = data_020d9128;
    idx = 0;
    func_0209bcc4(func_0202d9c4(self), &idx);
    if (idx < 5) {
        cfg.a = data_020d9d38[idx];
    }
    if (cfg.a != 0) {
        func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e,
                      func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(*(int *) (*(char **) ((char *) self + 0x100) + 0x830)))),
                      cfg.a, cfg.b, 0, 0);
        out->p = (char *) self + 0x104;
        out->b = *((unsigned char *) self + 0x122);
    }
    func_0202db48(self, data_020d9120);
}
