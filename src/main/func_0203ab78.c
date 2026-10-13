/* func_0203ab78 @ 0x0203ab78, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203ab78 {
    short unk_00;
    short s1;
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int i6;
};

struct UnkStruct_0203ab78_2 {
    char pad_00[0xfc];
    struct UnkStruct_0203ab78 unk_FC;
    char pad_11C[0x2c];
    struct UnkStruct_0203ab78 unk_148;
};

struct UnkStruct_0203ab78_3 {
    char data[16];
};

extern struct UnkStruct_0203ab78_2 *data_021c67a4;

extern void func_0203c210(struct UnkStruct_0203ab78_2 *p, struct UnkStruct_0203ab78 *f, int arg);
extern void func_01ffcbb0(struct UnkStruct_0203ab78_3 *local, struct UnkStruct_0203ab78_2 *p);
extern int func_0203c57c(struct UnkStruct_0203ab78_2 *p);
extern int func_0203c568(struct UnkStruct_0203ab78_2 *p);
extern int func_0203c548(struct UnkStruct_0203ab78_2 *p);
extern void func_0203bd84(struct UnkStruct_0203ab78_2 *p, struct UnkStruct_0203ab78_3 *local, int a, int b, int c);

void func_0203ab78(int arg)
{
    struct UnkStruct_0203ab78 *src;
    struct UnkStruct_0203ab78 *dst;
    struct UnkStruct_0203ab78_3 local;
    int v1, v2, v3;

    func_0203c210(data_021c67a4, &data_021c67a4->unk_FC, arg);

    src = &data_021c67a4->unk_FC;
    dst = &data_021c67a4->unk_148;
    dst->unk_00 = src->unk_00;
    dst->s1 = src->s1;
    dst->i0 = src->i0;
    dst->i1 = src->i1;
    dst->i2 = src->i2;
    dst->i3 = src->i3;
    dst->i4 = src->i4;
    dst->i5 = src->i5;
    dst->i6 = src->i6;

    func_01ffcbb0(&local, data_021c67a4);

    v1 = func_0203c57c(data_021c67a4);
    v2 = func_0203c568(data_021c67a4);
    v3 = func_0203c548(data_021c67a4);

    func_0203bd84(data_021c67a4, &local, v1, v2, v3);
}
