/* func_02094500 @ 0x02094500, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct GlobalData {
    int x, y, z;
    short w;
} GlobalData;

typedef struct UnkStruct_02094500 {
    unsigned char pad_00[0x18];
    int **ptr;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    unsigned char pad_2C[0x3c - 0x2c];
    short unk_3C;
    short unk_3E;
    short unk_40;
    unsigned char pad_42[0x5c - 0x42];
    int unk_5C;
} UnkStruct_02094500;

extern GlobalData data_021d5658;
extern void func_020ea78c(int *p, int v);
extern void func_020ea6e0(int *p, int v);
extern void func_02090db0(UnkStruct_02094500 *self);

void func_02094500(UnkStruct_02094500 *self)
{
    int local[3];
    int r4;
    int b, c, a;
    GlobalData *g = &data_021d5658;

    r4 = (short) (g->w + 0x8000);

    local[0] = 0;
    local[1] = 0;
    local[2] = 0x1000;

    self->unk_20 = g->x + (*self->ptr)[1];
    self->unk_24 = g->y + (*self->ptr)[2];
    self->unk_28 = g->z + (*self->ptr)[3];

    self->unk_5C = g->y + 0x333;

    func_020ea78c(local, 0xffffe000);
    func_020ea6e0(local, r4);

    b = local[1];
    c = local[2];
    a = local[0];
    self->unk_3C = (short) a;
    self->unk_3E = (short) b;
    self->unk_40 = (short) c;

    func_02090db0(self);
}
