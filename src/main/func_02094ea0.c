/* func_02094ea0 @ 0x02094ea0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
    unsigned short idx;
} EmitSrc;

typedef struct {
    void *pad_00;
    int x, y, z;
} QVec;

typedef struct {
    QVec *q;
} UnkStruct_02094ea0;

typedef struct {
    unsigned char pad_00[0x18];
    UnkStruct_02094ea0 *base;
    unsigned char pad_1C[0x20 - 0x1c];
    int wx, wy, wz;
    unsigned char pad_2C[0x3c - 0x2c];
    short sinv;
    short zero;
    short cosv;
} UnkStruct_02094ea0_2;

extern short FX_SinCosTable_[];
extern void func_02090db0(UnkStruct_02094ea0_2 *self);

void func_02094ea0(UnkStruct_02094ea0_2 *self, EmitSrc *src)
{
    unsigned short idx = src->idx;
    int idx2;

    self->wx = src->x + self->base->q->x;
    self->wy = src->y + self->base->q->y;
    self->wz = src->z + self->base->q->z;
    idx2 = (idx >> 4) << 1;
    self->sinv = FX_SinCosTable_[idx2];
    self->zero = 0;
    self->cosv = FX_SinCosTable_[idx2 + 1];
    func_02090db0(self);
}
