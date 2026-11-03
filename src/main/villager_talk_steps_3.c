/* villager_talk_steps_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02023980 @ 0x02023980, 0x80 bytes, Thumb
 * func_02023968 @ 0x02023968, 0x18 bytes, Thumb
 * func_020238f0 @ 0x020238f0, 0x78 bytes, Thumb
 * func_020238c8 @ 0x020238c8, 0x28 bytes, Thumb
 * func_02023864 @ 0x02023864, 0x64 bytes, Thumb
 */

struct SomeOuter;

struct UnkStruct_02023980;

struct UnkStruct_02023980_2;

struct GlobalData;

struct Global2;

struct GlobalData {
    int unk_00;
    unsigned char unk_04;
};

struct Global2 {
    int unk_00;
    int word1;
};

struct UnkStruct_02023980_2 {
    char pad_00[0x830];
    unsigned int unk_830;
};

struct SomeOuter {
    char pad_00[0xc8];
    struct Global2 unk_C8;
    char pad_D0[0x100 - 0xd0];
    struct UnkStruct_02023980_2 *inner;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[0x15a - 0x123];
    unsigned short unk_15A;
};

struct UnkStruct_02023980 {
    char *ptr;
    unsigned char unk_04;
};

typedef struct {
    char pad_00[0xc8];
    int unk_C8;
    int unk_CC;
    char pad_D0[0x30];
    void *ptr;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_020238f0;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020238f0_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Global1;

typedef struct {
    int unk_00;
    int unk_04;
} Global2;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} GlobalType;

typedef struct UnkStruct_02023864 {
    char pad_00[0x100];
    void *unk_100;
    char pad_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02023864;

typedef struct OutType {
    void *ptr;
    unsigned char unk_04;
} OutType;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern struct GlobalData data_020c8bf8;
extern struct Global2 data_020d94d0;
extern unsigned int func_0207b410(void *ptr);
extern void func_0209a77c(void *);
extern unsigned char data_021e5a2c[];
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern Global1 data_020c89e0;
extern Global2 data_020d8e58;
extern void *func_0209a778(void *record);
extern int func_0209bd44(void *);
extern void func_0209bb90(int, int);
extern GlobalType data_020c8aa8;

void func_02023980(struct SomeOuter *a, struct UnkStruct_02023980 *b)
{
    int val;
    int val2;
    int val3;
    int val4;
    int val5;
    val = func_020036e8(func_0208150c(a->inner->unk_830));
    val2 = data_020c8bf8.unk_00;
    val3 = (int) data_020c8bf8.unk_04;
    val4 = 0;
    val5 = 0;
    func_0202da38((void *) a, (void *) a->unk_104, (void *) (&a->unk_122), 0x1e, val, val2, val3, val4, val5);
    b->ptr = a->unk_104;
    b->unk_04 = a->unk_122;
    a->unk_15A = 0x5f;
    a->unk_C8 = data_020d94d0;
}

void func_02023968(void)
{
    func_0209a77c((void *) func_0207b410((void *) data_021e5a2c));
}

void func_020238f0(UnkStruct_020238f0 *s, UnkStruct_020238f0_2 *out)
{
    int a;
    int b;
    int c;
    int d;
    int e;
    a = func_020036e8(func_0208150c(*((int *) (((char *) s->ptr) + 0x830))));
    b = data_020c89e0.unk_00;
    c = data_020c89e0.unk_04;
    d = 0;
    e = 0;
    func_0202da38(s, s->unk_104, &s->unk_122, 0x1e, a, b, c, d, e);
    out->ptr = s->unk_104;
    out->byte = s->unk_122;
    {
        int tmp0 = data_020d8e58.unk_00;
        int tmp1 = data_020d8e58.unk_04;
        if (data_020c89e0.unk_04) {
            s->unk_C8 = tmp0;
        } else {
            s->unk_C8 = tmp0;
        }
        s->unk_CC = tmp1;
    }
}

void func_020238c8(void)
{
    void *record = func_0209a778((void *) func_0207b410((void *) ((unsigned int) data_021e5a2c)));
    if (func_0209bd44(record) != 0) {
        func_0209bb90((int) record, 1);
    }
}

void func_02023864(UnkStruct_02023864 *p0, OutType *out)
{
    unsigned int b = data_020c8aa8.unk_04;
    func_0202da38(p0, (char *) p0 + 0x104, (char *) p0 + 0x122, 0x1e,
                  func_020036e8(func_0208150c(*(unsigned int *) ((char *) p0->unk_100 + 0x830))), data_020c8aa8.unk_00, b, 1,
                  b);
    out->ptr = (char *) p0 + 0x104;
    out->unk_04 = p0->unk_122;
}
