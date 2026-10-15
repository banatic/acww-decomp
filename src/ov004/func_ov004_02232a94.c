/* func_ov004_02232a94 @ 0x02232a94, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02232a94 {
    char pad_00[8];
    int unk_08;
    char pad_0C[8];
    int unk_14;
    char pad_18[4];
    int unk_1C;
    int unk_20;
};
struct UnkStruct_02232a94_2 {
    char pad_00[0x20];
    struct UnkStruct_02232a94 *unk_20;
};
struct UnkStruct_02232a94_3 {
    struct UnkStruct_02232a94_2 *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};
extern struct UnkStruct_02232a94_3 *data_021c80bc;
extern int data_021c9b24;

extern int func_02055f40(void *, int, int);
extern int func_02055140(void *, int);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern int func_0205650c(void *, int, int);
extern void func_02056478(void *, int, int, int, int);
extern int func_02055e00(void *);
extern void func_020563dc(void *, int);

static __inline int atleast(unsigned int x, unsigned int n)
{
    return x > n;
}
static __inline struct UnkStruct_02232a94_2 *get(void)
{
    struct UnkStruct_02232a94_3 *g = data_021c80bc;
    if (!atleast(g->unk_04, 0) || !atleast(g->unk_08, 0) || g->unk_00 == 0) {
        return 0;
    }
    return g->unk_00;
}

void func_ov004_02232a94(char *self)
{
    struct UnkStruct_02232a94 *r = get()->unk_20;
    func_02055f40(self + 0x50, r->unk_08, r->unk_20);
    if (r->unk_14 != 0) {
        if (func_02055140(self + 0x50, data_021c9b24) != 0) {
            func_02055060(self + 0x50, r->unk_14, 0, 0x1000, 0, 0);
            func_02055050(self + 0x50);
        }
    }
    if (r->unk_1C != 0) {
        if (func_0205650c(self + 0x108, *(int *) (self + 0xac), data_021c9b24) != 0) {
            func_02056478(self + 0x108, r->unk_1C, 0, 0x1000, 0);
            func_020563dc(self + 0x108, func_02055e00(self + 0x50));
        }
    }
}
