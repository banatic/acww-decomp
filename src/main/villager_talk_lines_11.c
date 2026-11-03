/* villager_talk_lines_11: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02020104 @ 0x02020104, 0x64 bytes, Thumb
 * func_020200cc @ 0x020200cc, 0x38 bytes, Thumb
 * func_0202006c @ 0x0202006c, 0x60 bytes, Thumb
 */

struct UnkStruct_02020104_2 {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_02020104 {
    char pad_00[0x100];
    struct UnkStruct_02020104_2 *inner;
    char buffer[30];
    unsigned char byte;
};

struct Global {
    int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_02020104_3 {
    void *ptr;
    unsigned char byte;
};

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern struct Global data_020c8ce8;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(struct UnkStruct_02020104 *, char *, unsigned char *, int, int base, int offset, int scale,
                         int multiplier, int selected);
extern void func_02015774(int, int, const void *, int, int);
extern int func_02015828(int, int);
extern void func_0202dbf0(int, Pair);
extern Pair data_020d9310;
extern unsigned char data_021c1e84[];
extern int func_0206fc6c(void);
extern int func_0206fc44(void);
extern void func_02081b68(int, int, int);
extern int func_020984e8(void);
extern int func_02099870(int);
extern void func_0208016c(int, int, int, int);

void func_02020104(struct UnkStruct_02020104 *p, struct UnkStruct_02020104_3 *out)
{
    struct {
        int a;
        int b;
        int c;
        int d;
        int e;
    } local;

    local.a = func_020036e8(func_0208150c(p->inner->unk_830));
    local.b = data_020c8ce8.unk_00;
    local.c = data_020c8ce8.unk_04;
    local.d = 0;
    local.e = 0;

    func_0202da38(p, p->buffer, &p->byte, 30, local.a, local.b, local.c, local.d, local.e);
    out->ptr = p->buffer;
    out->byte = p->byte;
}

void func_020200cc(int param, int event)
{
    func_02015774(param, 23, (const void *) data_021c1e84, 10, 0);
    func_02015828(param, 6);
    func_0202dbf0(param, data_020d9310);
}

void func_0202006c(int *r0)
{
    int *r5;
    int r4;
    int r1;
    int r0_2;
    int r3;

    r5 = r0;
    if (func_0206fc6c() != 0) {
        r1 = *(int *) ((char *) r5 + 0x100);
        r4 = *(int *) ((char *) r1 + 0x830);
        r0_2 = *(int *) ((char *) r5 + 0x12c);
        if (r0_2 != 0) {
            r1 = func_0206fc44();
            r0_2 = *(int *) ((char *) r5 + 0x12c);
            func_02081b68(r0_2, r1, 0xa);
        } else {
            r5 = (int *) func_0206fc44();
            r3 = func_02099870(func_020984e8());
            func_0208016c(r4, (int) r5, 0xa, r3);
        }
    }
}
