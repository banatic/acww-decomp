/* villager_talk_part_10: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02028044 @ 0x02028044, 0x84 bytes, Thumb
 * func_02027ff8 @ 0x02027ff8, 0x4c bytes, Thumb
 */

struct UnkStruct_02028044 {
    int unk_00;
    unsigned char unk_04;
};

struct Secondary {
    char pad_00[0x830];
    int value;
};

struct Input {
    char pad_00[0x100];
    struct Secondary *sec;
    char data[0x1E];
    unsigned char byte;
};

struct Output {
    char *ptr;
    unsigned char byte;
};

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern struct UnkStruct_02028044 data_020c8e38;
extern struct UnkStruct_02028044 data_020c89b0;
extern int func_0202d9c4(struct Input *p);
extern int func_0209bc40(int arg);
extern int func_0208150c(int val);
extern int func_020036e8(int val);
extern int func_0202da38(struct Input *p, char *a, char *b, int c, int d, int e, int f, int g, int h);
extern int func_02015330(void *, void *, int, int, int);
extern void func_0202dbf0(void *, Pair);
extern void func_0209b56c(int);
extern Pair data_020d90b8;

void func_02028044(struct Input *p, struct Output *out)
{
    struct UnkStruct_02028044 *r4;
    int res;
    int v;

    r4 = 0;
    res = func_0209bc40(func_0202d9c4(p));

    switch (res) {
        case 0xa:
            r4 = &data_020c8e38;
            break;
        case 0x13:
            r4 = &data_020c89b0;
            break;
    }

    if (r4 != 0) {
        v = func_020036e8(func_0208150c(p->sec->value));
        func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 30, v, r4->unk_00, r4->unk_04, 0, 0);
    }

    out->ptr = (char *) p + 0x104;
    out->byte = p->byte;
}

void func_02027ff8(void *arg)
{
    if (func_0209bc40(func_0202d9c4((struct Input *) arg)) == 10) {
        func_02015330(arg, (char *) arg + 0x124, 2, 5, 0);
        func_0202dbf0(arg, data_020d90b8);
    }
    func_0209b56c(*(int *) ((char *) arg + 0x160));
}
