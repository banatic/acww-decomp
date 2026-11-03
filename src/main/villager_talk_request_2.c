/* villager_talk_request_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02028838 @ 0x02028838, 0x84 bytes, Thumb
 * func_020287e4 @ 0x020287e4, 0x54 bytes, Thumb
 */

typedef struct {
    char pad_00[0x830];
    unsigned int unk_830;
} UnkStruct_02028838;

typedef struct {
    char pad_00[0x100];
    UnkStruct_02028838 *sub;
    char pad_104[0x1E];
    unsigned char unk_122;
} UnkStruct_02028838_2;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} UnkStruct_02028838_3;

typedef struct {
    void *ptr;
    unsigned char byte;
} OutputStruct;

struct UnkStruct_020287e4 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_020287e4_2 {
    char pad_00[0x100];
    struct UnkStruct_020287e4 *sub;
    char pad_104[0x58];
    int unk_15C;
};

extern UnkStruct_02028838_3 data_020c8c30;
extern UnkStruct_02028838_3 data_020c8c10;
extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern unsigned int func_0208150c(unsigned int);
extern unsigned int func_020036e8(unsigned char *);
extern int func_0202da38(void *a, void *b, void *c, int d, int base, int offset, int scale, int h, int i);
extern char *func_02137550(void *, int);
extern int func_0207cb9c(int *, int *, int);
extern void func_02015e10(void *, int, int);
extern int data_021e5a2c;

void func_02028838(UnkStruct_02028838_2 *p1, OutputStruct *p2)
{
    UnkStruct_02028838_3 *dp = 0;
    int x;
    unsigned int v;

    x = func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) p1));
    switch (x) {
        case 10:
            dp = &data_020c8c30;
            break;
        case 19:
            dp = &data_020c8c10;
            break;
    }
    if (dp) {
        v = func_020036e8((unsigned char *) func_0208150c(p1->sub->unk_830));
        func_0202da38(p1, (char *) p1 + 0x104, (char *) p1 + 0x122, 30, v, dp->unk_00, dp->unk_04, 0, 0);
    }
    p2->ptr = (char *) p1 + 0x104;
    p2->byte = p1->unk_122;
}

void func_020287e4(struct UnkStruct_020287e4_2 *obj)
{
    int local;
    func_02137550(&local, 4);
    local = (int) func_0208150c(obj->sub->unk_830);
    obj->unk_15C = (int) func_0208150c(func_0207cb9c(&data_021e5a2c, &local, 1));
    func_02015e10(obj, obj->unk_15C, 1);
}
