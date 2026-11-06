/* villager_talk_part_6: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202760c @ 0x0202760c, 0x78 bytes, Thumb
 * func_020275a4 @ 0x020275a4, 0x68 bytes, Thumb
 * func_02027540 @ 0x02027540, 0x64 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Global1;

typedef struct {
    int unk_00;
    int unk_04;
} Global2;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0202760c;

typedef struct {
    char pad_00[0xc8];
    Global2 unk_C8;
    char pad_D0[0x30];
    void *unk_100;
    char arr_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0202760c_2;

typedef struct {
    int lo;
    int hi;
} DoubleWord;

typedef struct UnkStruct_020275a4 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_020275a4;

typedef struct Param {
    char pad_00[0x100];
    UnkStruct_020275a4 *sub;
    char pad_104[0x5c];
    int unk_160;
} Param;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02027540;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(UnkStruct_0202760c_2 *a, char *p1, unsigned char *p2, int len, int arg5, int arg6, int arg7, int arg8,
                         int arg9);
extern Global1 data_020c8e10;
extern Global2 data_020d94b0;
extern int func_0209b4d4(int);
extern void func_0209bb90(int, int);
extern int func_0209b4cc(int, int);
extern void func_0207bae8(int *, int, int, int);
extern int func_02015094(void *);
extern int data_021e5a2c;
extern DoubleWord data_020d94a8;
extern void func_0202dbf0(void *, DoubleWord);
extern struct {
    int field0;
    unsigned char field4;
} data_020c8e00;

void func_0202760c(UnkStruct_0202760c_2 *a, UnkStruct_0202760c *out)
{
    int x;
    int g1_word;
    int g1_byte;
    int z1, z2;

    x = func_020036e8(func_0208150c(*(int *) ((char *) a->unk_100 + 0x830)));
    g1_word = data_020c8e10.unk_00;
    g1_byte = data_020c8e10.unk_04;
    z1 = 0;
    z2 = 0;

    func_0202da38(a, a->arr_104, &a->unk_122, 30, x, g1_word, g1_byte, z1, z2);

    out->ptr = a->arr_104;
    out->byte = a->unk_122;
    a->unk_C8 = data_020d94b0;
}

void func_020275a4(Param *param)
{
    int r4;
    int r2;

    func_0209bb90(func_0209b4d4(param->unk_160), 1);
    r4 = func_0209b4cc(param->unk_160, 0);
    r2 = func_0208150c(param->sub->unk_830);
    func_0207bae8(&data_021e5a2c, r4, r2, -20);
    func_02015094(param);
    func_0202dbf0(param, data_020d94a8);
}

void func_02027540(void *self, UnkStruct_02027540 *out)
{
    int local0, local1, local2, local3, local4;
    void *p1;
    void *p2;

    p1 = *(void **) ((char *) self + 0x100);
    p2 = *(void **) ((char *) p1 + 0x830);

    local0 = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((unsigned int) p2)));
    local1 = data_020c8e00.field0;
    local2 = data_020c8e00.field4;
    local3 = 0;
    local4 = 0;

    func_0202da38((UnkStruct_0202760c_2 *) ((int) self), (char *) ((int) ((char *) self + 0x104)),
                  (unsigned char *) self + 0x122, 30, local0, local1, local2, local3, local4);

    out->ptr = (char *) self + 0x104;
    out->byte = *(unsigned char *) ((unsigned char *) self + 0x122);
}
